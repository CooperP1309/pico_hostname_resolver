<div align="center">
  <h1>Pi Pico W Hostname Resolver</h1>
</div>

An example repo that demonstrates resolving hostnames into IP addresses over the internet. 

This makes use of the lwip/dns library to carry this out. With that said, this demonstration is 
ideal for those that use the following config:

lwipopts.h (lwip options file):

    #define NO_SYS 1

CMakeList.txt:

    pico_cyw43_arch_lwip_threadsafe_background

I.e. This demonstration is for those carrying out dns resolution without the POSIX library.
As for those not using "...threadsafe_background", the logic is the same, just with manual
calls of the poll function "cyw43_arch_poll()" in the while(1) loop in main.

Quick Note: 

    If you're unfamiliar with DNS resolving, the pico must be connected to a network with a 
    valid gateway to the internet for this to work. Unless you have a local DNS implementation.


<h2>Building the Project</h2>

To build this project, you must have the pico-sdk installed properly.

IF: You're building from a raspberry Pi (as a PC to develop on) use the following setup script:
https://raw.githubusercontent.com/raspberrypi/pico-setup/master/pico_setup.sh

IF: You're building from a linux environment see page 32 "Manually Configure your Environment":
https://pip-assets.raspberrypi.com/categories/610-raspberry-pi-pico/documents/RP-008276-DS-1-getting-started-with-pico.pdf?disposition=inline

Step 1:
    Give executable permission to the build script. In the root of this repo, run the following:

        sudo chmod +x build.sh

Step 2:
    Execute build script. In the root of this repo, run the following:

        ./build.sh

Step 3:
    Flash to the Pico. With the pico in flash mode (plugged into a usb port whilst the 'BOOTSEL' button is held down), run the following command from the repo root:

        cp build/pico_hostname_resolver.uf2 /media/'username'/RPI-RP2

Step 4:
    To observe the output, install minicom (if you enjoy pain) and run the following command:

        minicom -D /dev/ttyACM0 -b 115200

    Note: ttyACM0 is the first file your board will talk to if no other device occupies it.
          If this doesn't work, try "ls /dev/ttyACM*" to see what other ttyACM files are
          currently running.