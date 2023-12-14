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

while true; do
    rm -f pip
    mkfifo pip

    # Listener
    nc -lk "$port" 0< pip | {

        # Service
        setarch "$(arch)" -R "$startup" 

    } 1>pip

    # Cleanup before waiting for the next connection
    rm -f pip
done
