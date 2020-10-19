#!/bin/bash

ofono-phonesim -p 12345 /usr/share/phonesim/default.xml &
ofono/test/enable-modem /phonesim
pulseaudio --kill
pulseaudio --start