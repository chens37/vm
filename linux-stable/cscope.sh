#!/bin/bash

find . -name "*.h" -o -name "*.c" -o -name "*.dtsi" -o -name "*.dts" -o -name "*.asm" -o -name "*.s" > cscope.files
cscope -bkq -i cscope.files
ctags -R
