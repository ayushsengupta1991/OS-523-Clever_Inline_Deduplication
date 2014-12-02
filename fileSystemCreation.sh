#!/bin/bash

clear

echo "Creating File System of size 10000 bytes"

echo "Your new file system is FS"

dd if=/dev/zero of=FS bs=1 count=10000
