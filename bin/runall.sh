#!/bin/bash 
for file in ./cut_5s/*.wav ; do
#    echo ${file}
    ./recog $file
done
