#!/bin/sh
cd $(dirname "$0")
docker build -t marcbal/sfmltetris-linux -f Dockerfile.linux .
docker run --rm -d --name sfmltetris-linux marcbal/sfmltetris-linux sleep 100 > /dev/null
mkdir -p bin
docker cp -L sfmltetris-linux:/data/bin/ ./bin
docker stop sfmltetris-linux > /dev/null