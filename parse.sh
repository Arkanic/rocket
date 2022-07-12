#!/usr/bin/bash

rm -rf out

mkdir out out/json
node parsedata.js $1
FRAMERATE=$?

echo "Will start ffmpeg with framerate $FRAMERATE in dir $1"
read -p "Press enter to continue"
ffmpeg -framerate $FRAMERATE -i $1/frames/frame-%d.jpg out/video.mp4

echo
echo
echo "done"