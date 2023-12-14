#!/bin/bash

port=8000
path=/home/os/buffer-overflow-demo/
startup=./out/morsecode

cd "$path" || exit 1

cleanup() {
    rm -f pip
    exit 0
}

trap cleanup EXIT

# Listener (executed only once)
rm -f pip
mkfifo pip

nc -lk "$port" 0< pip | {

    # Startup program (executed in a loop)
    while true; do
        setarch "$(arch)" -R "$startup"
    done

} 1>pip

# Cleanup after listener exits
rm -f pip
