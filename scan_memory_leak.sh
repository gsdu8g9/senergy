#!/usr/bin/env bash

rm -rf log.txt
valgrind bin/senergy-dns > log.txt 2>&1
