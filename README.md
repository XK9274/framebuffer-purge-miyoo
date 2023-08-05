# framebuffer-purge-miyoo
DEMO APP.
Save/Restore the framebuffer state to avoid black screens/corrupt FB parameters

## Overview 
Test files to restore the screen after something causes bad FB params or a blackscreen but you still have key event control (can hear clicks in the background)

## Usage
- call `fbpurge save` before the action that causes the problem

- call `fbpurge restore` after 

- cleanup `/tmp/framebuffer_vinfo.bin` (or add this to source, whatever floats your boat)

The problem is, you may also have to kill anything that has a lock on `/dev/fb0` (in this case it's batmon, keymon, /dev/l and whatever app is currently causing the issue or running at the time (in our case `prompt`))
