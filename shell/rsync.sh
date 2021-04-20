#!/bin/bash
sshpass -p Aaa123 rsync -avr -e 'ssh -p 7995' ./ pi@tc.ubiwifi.cn:/home/pi/dev/video/
