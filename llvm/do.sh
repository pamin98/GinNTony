#!/bin/bash

opimize="";
print_ir=false;
print_asm=false;
filename="";

while (( "$#" )); do 
    if [[ "$1" == "-o" ]]; then
        optimize="-o"
    elif [[ "$1" == "-f" ]]; then
        print_asm=true
    elif [[ "$1" == "-i" ]]; then
        print_ir=true
    else
        filename=$1
    fi
    shift 
done

./GinNTony $optimize $filename

if [ $? -ne 0 ]; then
    echo "Error while compiling tony to LLVM IR"
fi

if [ "$print_ir" = true ] ; then
    cat module.s
fi

llc module.imm -o module.asm

if [ $? -ne 0 ]; then
    echo "Error while compiling LLVM IR to ASM"
fi

if [ "$print_asm" = true ] ; then
    cat module.asm
fi

clang -o module.out module.asm lib.a -lgc

if [ $? -ne 0 ]; then
    echo "Error while linking with the GC and built in functions"
fi

rm module.s module.imm module.asm

./module.out

