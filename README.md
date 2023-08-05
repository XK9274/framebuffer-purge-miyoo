# framebuffer-purge-miyoo
Save/Restore the framebuffer state to avoid black screens/corrupt FB parameters

## Overview 
Test files to restore the screen after something causes bad FB params or a blackscreen but you still have key event control (can hear clicks in the background)

## Usage
- call `fbpurge save` before the action that causes the problem

- call `fbpurge restore` after 

- cleanup `framebuffer_vinfo.bin` (or add this to source, whatever floats your boat)
