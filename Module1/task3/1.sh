#!/bin/bash

grep -h syslogd /var/log/* 2>/dev/null > errors.log