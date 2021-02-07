#!/bin/bash
rm -rf bin/out
gcc -I headers \
sources/hash.c sources/main.c \
-o bin/out
bin/out