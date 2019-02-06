This is a minimal container to work with this repo from any system using a docker container to compile in

# Build container locally
`docker build -t bmagyar/ros-control2 .`

# Run container and bind to local workspace
`docker run -it -v "$HOME/480/workspaces/rosin_ws:/home/bence/ws" -e LOCAL_USER_ID=`id -u $USER` -e LOCAL_GROUP_ID=`id -g $USER` -e LOCAL_GROUP_NAME=`id -gn $USER` bmagyar/ros-control2 /bin/bash`
