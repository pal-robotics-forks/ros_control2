#!/bin/bash

# enable connections from containers
xhost local:root

export LOCAL_USER_ID=`id -u $USER`
export LOCAL_GROUP_ID=`id -g $USER`
export LOCAL_GROUP_NAME=`id -gn $USER`
DOCKER_USER_ARGS="--env LOCAL_USER_ID --env LOCAL_GROUP_ID --env LOCAL_GROUP_NAME"

docker run -it --rm \
    $DOCKER_USER_ARGS \
    -e DISPLAY=$DISPLAY \
    -v /tmp/.X11-unix:/tmp/.X11-unix \
    -v $HOME/docker_rosin/.config:/home/user/.config \
    -v $HOME/docker_rosin/qtcreator:/home/user/qtcreator \
    -v $HOME/docker_rosin/ws:/home/user/ws \
    ros-control2:latest bash
