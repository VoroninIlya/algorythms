#! /bin/bash

#rm -r release

mkdir release

make compile_flags="-O2 -g" --directory=release --makefile=../makefile
