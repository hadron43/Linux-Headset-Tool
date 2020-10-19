# Bluetooth Headset Utility Program

Ubuntu (and many other distros of Linux) doesn't recognize the microphone of connected bluetooth headset. This leads to issues while attending calls, etc. This program aims at solving this issue.

## Dependencies

- ofono
- ofono-phonesim

## Setup

Source : ![Blog Link](https://itectec.com/ubuntu/ubuntu-cant-change-profile-to-hsp-for-bluetooth-headset/)

1. Clone this repository

```sh
git clone https://github.com/hadron43/Linux-Headset-Tool
```

2. Make sure you have make installed on your system. If not, install it using:

```sh
sudo apt install make
```

3. Move to the cloned repo on your terminal. If you are using `apt` on your system, run `make`, or else, run `make install` and then manaully install additional dependencies `ofono` and `ofono-phonesim` on your system.

### Config pulseaudio to use ofono

***These steps have been deliberately kept manual, to prevent any damage to your configuration files***

1. Goto `/etc/pulse/default.pa` find the line `load-module module-bluetooth-discover` and change it in `load-module module-bluetooth-discover headset=ofono`.

2. Add the user pulse to group bluetooth to grant the permission: `sudo usermod -aG bluetooth pulse` (probably it's already correct)

3. **VERY IMPORTANT**: To grant the permission, add this to `/etc/dbus-1/system.d/ofono.conf` (before ):

```sh
    <policy user="pulse">
      <allow send_destination="org.ofono"/>
    </policy>
```

### Usage

- `headset -s [ipAddr]` : Saves the ip address of your device
- `headset -c` : Connect to your saved device
- `headset -h` : Switch to handfree mode
- `headset -a` : Switch to A2DP mode
- `headset --help` : Show detailed help
