#!/bin/bash
./GinNTony $1
llc module.imm -o module.asm
clang -o module.out module.asm lib.a -lgc
# ./module.out
