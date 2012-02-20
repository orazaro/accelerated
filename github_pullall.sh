#!/bin/sh
for d in `find . -maxdepth 1 -type d`;do echo $d" ===>";cd $d && git pull ; cd ..;done
