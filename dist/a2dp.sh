#!/bin/bash

ofono/test/disable-modem /phonesim
pulseaudio --kill
sleep 2
pulseaudio --start

# Uncomment these, if you have pulseeffects installed on your system
# pulseeffects --quit
# pulseeffects &

