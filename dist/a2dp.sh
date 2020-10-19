#!/bin/bash

ofono/test/disable-modem /phonesim
pulseaudio --kill
pulseaudio --start
pulseeffects --quit
pulseeffects &