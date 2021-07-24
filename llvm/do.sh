#!/bin/bash

opimize="";
print_ir=false;
print_asm=false;
filename="";

while (( "$#" )); do 
    if [[ "$1" == "-O" ]]; then
        optimize="-O"
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

filename=${filename##*/}
IFS='.' read -r filename _ <<< "$filename"

if [ $? -ne 0 ]; then
    echo "Error while compiling tony to LLVM IR"
fi

if [ "$print_ir" = true ] ; then
    cat $filename.s
fi

llc $filename.imm -o $filename.asm
mv $filename.s $filename.imm

if [ $? -ne 0 ]; then
    echo "Error while compiling LLVM IR to ASM"
fi

if [ "$print_asm" = true ] ; then
    cat $filename.asm
fi

clang -o $filename.out $filename.asm lib.a -lgc

if [ $? -ne 0 ]; then
    echo "Error while linking with the GC and built in functions"
fi

./$filename.out

