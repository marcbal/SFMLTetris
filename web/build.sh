#!/bin/bash

docker build -t marcbal/sfmltetris-web:latest -f web.Dockerfile .
docker push marcbal/sfmltetris-web:latest

docker build -t marcbal/sfmltetris-db:latest -f db.Dockerfile .
docker push marcbal/sfmltetris-db:latest