#!/bin/sh
cd $(dirname "$0")
if [ $# -ne 0 ]; then
    args="$@"
else
    args="release"
fi
docker build --progress=plain --build-arg TARGET="$args" -t marcbal/sfmltetris-linux -f Dockerfile.linux .
docker run --rm -d --name sfmltetris-linux marcbal/sfmltetris-linux sleep 100 > /dev/null
mkdir -p bin
rm -rf bin/*linux*
docker cp -L sfmltetris-linux:/data/bin ./
docker stop sfmltetris-linux > /dev/null
docker image rm marcbal/sfmltetris-linux