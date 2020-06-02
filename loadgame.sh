#!/bin/bash

mkfifo $1
cat -f $1 | ./main
