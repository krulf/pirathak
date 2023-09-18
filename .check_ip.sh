#!/bin/bash

current_ip=$(curl -s ifconfig.me)
while true; do
    new_ip=$(curl -s ifconfig.me)
    if [ "$current_ip" != "$new_ip" ]; then
        echo "current ip $current_ip -> new ip $new_ip"
        # Add your command to be executed here
        current_ip="$new_ip"
        firefox "hvadnu.dk"
    fi
    sleep 1 # Check every 60 seconds, you can adjust this value
done
