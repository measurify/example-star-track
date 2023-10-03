#!/bin/bash

gphoto2 --set-config capturetarget=1 #save photo to memory card
gphoto2 --trigger-capture --wait-event=FILEADDED
