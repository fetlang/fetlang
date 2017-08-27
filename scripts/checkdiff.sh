#!/bin/bash
# Return 0 if two files are different
# Return 1 otherwise
! cmp $1 $2
