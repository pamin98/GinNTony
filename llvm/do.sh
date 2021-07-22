#!/bin/bash
./GinNTony $1
llc-12 module.imm -o module.asm
clang -o module.out module.asm lib.a -lgc
./module.out
