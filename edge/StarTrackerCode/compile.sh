#!/bin/bash

sudo pkill -9 starTracker
gcc -Wall -pthread -o starTracker starTracker.c -lpigpio -lrt
