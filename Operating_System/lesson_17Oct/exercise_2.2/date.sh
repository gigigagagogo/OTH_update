#!/bin/bash

echo  $(date +%F_%T) > myDate.txt
echo $(whoami) >> myDate.txt
ls blah >> myDate.txt 2>&1
