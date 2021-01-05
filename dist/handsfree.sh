#!/bin/bash

ofono-phonesim -p 12345 /usr/share/phonesim/default.xml &
ofono/test/enable-modem /phonesim
sleep 2
pulseaudio --kill
sleep 2
pulseaudio --start