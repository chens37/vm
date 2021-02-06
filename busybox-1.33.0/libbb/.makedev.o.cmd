cmd_libbb/makedev.o := arm-linux-gnueabi-gcc -Wp,-MD,libbb/.makedev.o.d   -std=gnu99 -Iinclude -Ilibbb  -include include/autoconf.h -D_GNU_SOURCE -DNDEBUG -D_LARGEFILE_SOURCE -D_LARGEFILE64_SOURCE -D_FILE_OFFSET_BITS=64 -DBB_VER='"1.33.0"'  -Wall -Wshadow -Wwrite-strings -Wundef -Wstrict-prototypes -Wunused -Wunused-parameter -Wunused-function -Wunused-value -Wmissing-prototypes -Wmissing-declarations -Wno-format-security -Wdeclaration-after-statement -Wold-style-definition -finline-limit=0 -fno-builtin-strlen -fomit-frame-pointer -ffunction-sections -fdata-sections -fno-guess-branch-probability -funsigned-char -static-libgcc -falign-functions=1 -falign-jumps=1 -falign-labels=1 -falign-loops=1 -fno-unwind-tables -fno-asynchronous-unwind-tables -fno-builtin-printf -Os     -DKBUILD_BASENAME='"makedev"'  -DKBUILD_MODNAME='"makedev"' -c -o libbb/makedev.o libbb/makedev.c

deps_libbb/makedev.o := \
  libbb/makedev.c \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/stdc-predef.h \
  include/platform.h \
    $(wildcard include/config/werror.h) \
    $(wildcard include/config/big/endian.h) \
    $(wildcard include/config/little/endian.h) \
    $(wildcard include/config/nommu.h) \
  /home/shichen/vm/crosstools/lib/gcc/arm-linux-gnueabi/7.5.0/include-fixed/limits.h \
  /home/shichen/vm/crosstools/lib/gcc/arm-linux-gnueabi/7.5.0/include-fixed/syslimits.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/limits.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/libc-header-start.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/features.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/sys/cdefs.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/wordsize.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/long-double.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/gnu/stubs.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/gnu/stubs-soft.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/posix1_lim.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/local_lim.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/linux/limits.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/posix2_lim.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/xopen_lim.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/stdio_lim.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/byteswap.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/byteswap.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/types.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/typesizes.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/byteswap-16.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/endian.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/endian.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/uintn-identity.h \
  /home/shichen/vm/crosstools/lib/gcc/arm-linux-gnueabi/7.5.0/include/stdint.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/stdint.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/wchar.h \
  /home/shichen/vm/crosstools/lib/gcc/arm-linux-gnueabi/7.5.0/include/stdbool.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/unistd.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/posix_opt.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/environments.h \
  /home/shichen/vm/crosstools/lib/gcc/arm-linux-gnueabi/7.5.0/include/stddef.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/confname.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/getopt.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/sys/sysmacros.h \
  /home/shichen/vm/crosstools/arm-linux-gnueabi/libc/usr/include/bits/sysmacros.h \

libbb/makedev.o: $(deps_libbb/makedev.o)

$(deps_libbb/makedev.o):
