# Worms Ultimate Mayhem Mouse Fix
This is a simple plugin which aims to fix mouse movement, in vanilla
game cursor jumps around position and is overall stuttery.


## Possible Reason

This plugin disables one function which sets the cursor position with
system call "SetCursorPos" and also to internal game position, there is another function which also sets
cursor position but this one only sets the position to internal game position.

It looks like there might be some kind of race error between these two functions, disabling
the system one seems to fix the cursor stuttering.

# Installation
Extract .zip file from Releases section to root game folder (where executable is).

This project uses [Ultimate ASI Loader](https://github.com/ThirteenAG/Ultimate-ASI-Loader).