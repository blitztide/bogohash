#!/bin/bash

for i in `seq 1 100`;
do
	INPUT=`dd if=/dev/random bs=10 count=1 2>/dev/null | base64 -w0`
	./bogohash $INPUT
done
