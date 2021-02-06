#include <linux/types.h>
#include <linux/mutex.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/uaccess.h>
#include <linux/wait.h>
#include <linux/cdev.h>
#include <linux/slab.h>
#include <linux/init.h>

#define GLOBALMEM_MAJOR 250
#define GLOBALMEM_SIZE 0x1000
#define GLOBALMEM_NUM   10

struct globalmem_dev {
    struct cdev cdev;
    struct mutex mutex;
    int len;
    u8  mem[GLOBALMEM_SIZE];

    wait_queue_head_t r_wait;
    wait_queue_head_t w_wait;
    
    struct fasync_struct *async_queue;
};

static struct globalmem_dev *globalmem_devp;

static int globalmem_major = GLOBALMEM_MAJOR;


ssize_t globalmem_write(struct file *filp, const char __user *buf, size_t cnt, loff_t *ppos)
{
    ssize_t ret;
    struct globalmem_dev *dev = filp->private_data;
    
    DECLARE_WAITQUEUE(wait,current);

    mutex_lock(&dev->mutex);
    
    add_wait_queue(&dev->w_wait,&wait);
    while(dev->len == GLOBALMEM_SIZE) {
    
        if(filp->f_flags & O_NONBLOCK) {
            ret = -EAGAIN;
            goto out;
        }
        __set_current_state(TASK_INTERRUPTIBLE);
        mutex_unlock(&dev->mutex);

        schedule();
        if(signal_pending(current)) {
            ret = -ERESTARTSYS;
            goto out2;
        }
        mutex_lock(&dev->mutex);
    }

    if(cnt > (GLOBALMEM_SIZE - dev->len))
        cnt = GLOBALMEM_SIZE - dev->len;
    
    if(copy_from_user(dev->mem+dev->len,buf,cnt)) {
        ret = -EFAULT;
        goto out;
    }else {
        dev->len +=cnt;
        printk(KERN_INFO "written %d bytes,fifo len:%d\n",cnt,dev->len);
        wake_up_interruptible(&dev->r_wait);
        if(dev->async_queue) {
            kill_fasync(&dev->async_queue,SIGIO,POLL_IN);
            printk(KERN_DEBUG "%s kill SIGIO\n",__func__);
        }
            
        ret = cnt;
    }


out:
    mutex_unlock(&dev->mutex);
out2:
    remove_wait_queue(&dev->w_wait,&wait);
    set_current_state(TASK_RUNNING);
    return ret;
}

ssize_t globalmem_read(struct file *filp,char __user *buf,size_t cnt,loff_t *ppos)
{
    ssize_t ret;
    struct globalmem_dev *dev = filp->private_data;

    DECLARE_WAITQUEUE(wait,current);

    mutex_lock(&dev->mutex);
    add_wait_queue(&dev->r_wait,&wait);
    while(dev->len == 0) {
        if(filp->f_flags & O_NONBLOCK) {
            ret = -EFAULT;
            goto out;
        }

        __set_current_state(TASK_INTERRUPTIBLE);
        mutex_unlock(&dev->mutex);

        schedule();
        if(signal_pending(current)) {
            ret = ERESTARTSYS;
            goto out2;
        }
        mutex_lock(&dev->mutex);
    }

    if(cnt > dev->len) 
        cnt = dev->len;
    
    if(copy_to_user(buf,dev->mem,cnt)) {
        ret = -EFAULT;
        goto out;
    }else {
        memcpy(dev->mem,dev->mem+cnt,dev->len-cnt);
        dev->len = dev->len - cnt;
        printk(KERN_INFO "read %d bytes,fifo len:%d\n",cnt,dev->len);
        wake_up_interruptible(&dev->w_wait);

        ret = cnt;
    }


out:
    mutex_unlock(&dev->mutex);
out2:
    remove_wait_queue(&dev->r_wait,&wait);
    set_current_state(TASK_RUNNING);
    return ret;
}

int globalmem_fasync(int fd,struct file *filp,int mode)
{
    struct globalmem_dev *dev = filp->private_data;

    return fasync_helper(fd,filp,mode,&dev->async_queue);
}

int globalmem_release(struct inode *inode, struct file *filp)
{
    globalmem_fasync(-1,filp,0);
    return 0;
}

int globalmem_open(struct inode *inode,struct file *filp)
{
    struct globalmem_dev *dev = container_of(inode->i_cdev,struct globalmem_dev,cdev);

    filp->private_data = dev;

    return 0;
}


const struct file_operations globalmem_fops = {
    .owner = THIS_MODULE,
    .read = globalmem_read,
    .write = globalmem_write,
    .open = globalmem_open,
    .release = globalmem_release,
    .fasync = globalmem_fasync,
};


int globalmem_setup(struct globalmem_dev *dev,int index)
{
    int ret;

    cdev_init(&dev->cdev,&globalmem_fops);   

    ret = cdev_add(&dev->cdev,MKDEV(globalmem_major,index),1);

    mutex_init(&dev->mutex);

    init_waitqueue_head(&dev->w_wait);
    init_waitqueue_head(&dev->r_wait);


    if(ret)
        return -1;

    return 0;
}


static int __init globalmem_init(void)
{
    int i;
    int error;
    dev_t devno = MKDEV(globalmem_major,0);    

    printk("run......................\n");

    if(devno) 
        error = register_chrdev_region(devno,GLOBALMEM_NUM,"globalmem");
    else {
        error = alloc_chrdev_region(&devno,0,GLOBALMEM_NUM,"globalmem");
        globalmem_major = MAJOR(devno);
    }

    if(error < 0) {
        printk(KERN_INFO "register chrdev error\n");
        return error;
    }
    
    globalmem_devp = kzalloc(sizeof(struct globalmem_dev)*GLOBALMEM_NUM,GFP_KERNEL);
    
    if(!globalmem_devp) {
        printk("kzalloc error\n");
        goto fail_malloc;
    }

    for(i = 0;i < GLOBALMEM_NUM;i++) {
        globalmem_setup(globalmem_devp+i,i);
    }

    return 0;
fail_malloc:
    unregister_chrdev_region(devno,GLOBALMEM_NUM);
    return -1;
}

static void __exit globalmem_exit(void)
{
    int i;

    for(i = 0;i < GLOBALMEM_NUM;i++) {
        cdev_del(&(globalmem_devp+i)->cdev);
    }

    kfree(globalmem_devp);
    unregister_chrdev_region(MKDEV(globalmem_major,0),GLOBALMEM_NUM);
}

module_init(globalmem_init);

module_exit(globalmem_exit);

MODULE_LICENSE("GPL");


