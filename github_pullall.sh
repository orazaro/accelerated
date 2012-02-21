#!/bin/sh
for d in `ls`;do if [ -d $d ]; then echo "===> $d";cd $d && git pull ; cd ..; fi;done
