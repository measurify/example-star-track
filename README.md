#Design and implementation of an embedded star tracker

##Overview

This project has been developed in order to support a camera during long exposure photos to stars.
The aim is to use a Raspberry pi 3 as a controller to pilot a stepper motor which holds the camera stationary relatively to the sky. Another function of the Raspberry is to remotely control the camera in order to shoot multiple photos without using the camera buttons.

##Quickstart

*Setting up the Raspberry.*

To make the Raspberry ready to work there are two passages that should be executed:
	- Put the folder "StarTrackerCode" directly on the desktop of the Raspberry.
	- In the console type "sudo nano /etc/rc.local" to open the file rc.local and, before the line "exit 0" insert the following: "sudo /home/pi/Desktop/StarTrackerCode/starTracker &".
	  This instruction will make the raspberry execute our code at the boot of the system.
	  Note that the "&" at the end is very important, without it the completion of the boot will be blocked.
	  
*Turning on the system*

To turn on the sistem and the program at this point you have to just plug in a power supply to power on the raspberry. Give it enough time to complete the boot.
The camera can be connected via USB cable to the raspberry either before or after the startup.
Please note that, in order to make the remote control of the camera possibile, the USB cable should be able to transfer data. It will not work with a USB cable that only works to recharge.

*Using the system*

* Orient the structure (for example using a easel) so that the rotation axis is pointed to the North Star and the upper side of the triangle opens from east through west.
* Fix the camera to the upper side of the triangle.
* Orient the camera so that it frames the portion of the sky that you want to capture.
* Start the movement of the motor with the switch button.
* Press the push button to start capturing photos. While camera is capturing the led will be turned on and it will be automatically switched off when the camera ends shooting.