#!/bin/bash

make all
./test

./sparse A B

gzip -k A
gzip -k B
echo "Gzipped"

gzip -cd B.gz | ./sparse C

./sparse A D -b 100

echo $(stat -c "%n = %s" A A.gz B B.gz C D)