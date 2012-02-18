#!/bin/sh
for d in `find . -type d -depth 1`;do echo $d" ===>";cd $d && git pull ; cd ..;done
