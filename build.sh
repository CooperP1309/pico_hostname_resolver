#!/bin/bash

# begin by setting wifi SSID and PASSWORD from user input
echo "What is your wifi SSID (your wifi name)?"
read ssid
echo "What is your wifi password?"
read password
echo "#define SSID \"$ssid\"
#define PASSWORD \"$password\"" > src/secret_wifi_creds.h

# enable error checking to bail if compiling fails
set -e

# change to project root
cd "$(dirname "$0")"

# ensure clean build wiping
rm -rf build

# invoke CMake with pico_w board type
cmake -S . -B build \
  -DPICO_SDK_PATH=$HOME/pico/pico-sdk \
  -DPICO_BOARD=pico_w \

# Build with all cores
cmake --build build --parallel

echo
echo "Compiled UF2 file location:"
echo "   $(realpath build/pico_hostname_resolver.uf2)"
echo
