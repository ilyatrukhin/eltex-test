#!/bin/bash

grep -Eiorh '([[:alnum:]_.-]+@[[:alnum:]_.-]+?\.[[:alpha:].]{2,6})' "$@" /etc/* 2>/dev/null | 
sort | uniq | grep @ | tr "\n" "," > emails.lst
