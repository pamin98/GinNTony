#!/bin/bash

./minibasic < $1 > a.ll
llc a.ll -o a.s
clang -o a.out a.s libminibasic.a -lgc
