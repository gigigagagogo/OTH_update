#!/bin/bash

if grep -w "2024" "myDate.txt"; then
	echo "yes"
else
	echo "no"
fi
