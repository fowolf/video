#!/bin/bash
sshpass -p Aaa123 rsync -avr -e 'ssh -p 7995' ./include pi@tc.ubiwifi.cn:/home/pi/dev/video/
sshpass -p Aaa123 rsync -avr -e 'ssh -p 7995' ./shell pi@tc.ubiwifi.cn:/home/pi/dev/video/
sshpass -p Aaa123 rsync -avr -e 'ssh -p 7995' ./source pi@tc.ubiwifi.cn:/home/pi/dev/video/
sshpass -p Aaa123 rsync -avr -e 'ssh -p 7995' ./CMakeLists.txt pi@tc.ubiwifi.cn:/home/pi/dev/video/CMakeLists.txt
sshpass -p Aaa123 rsync -avr -e 'ssh -p 7995' ./main.cpp pi@tc.ubiwifi.cn:/home/pi/dev/video/main.cpp
