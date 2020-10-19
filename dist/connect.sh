#!/bin/bash

rfkill unblock bluetooth
bluetoothctl power on
bluetoothctl connect $1
exit