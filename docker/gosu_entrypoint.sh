#!/bin/bash

# Credit goes to https://denibertovic.com/posts/handling-permissions-with-docker-volumes/
# Modified to allow adding groups and mounting volumes as home of the user

#If no command argument is given, run bash
if [ $# -eq 0 ]; then
    cmd=bash
else
    cmd=$@
fi

if [ -z $LOCAL_USER_ID ]; then
    #If this variable is not set, use standard docker approach
    $cmd
    exit $?
fi
USER_ID=${LOCAL_USER_ID}
USER_NAME=${LOCAL_USER_NAME:-user}
GROUP_ID=${LOCAL_GROUP_ID}

echo "Associating docker user $USER_NAME to host's user with UID $USER_ID"
if [ $(getent passwd $USER_NAME) > /dev/null ]; then
    usermod -o -u $USER_ID $USER_NAME
else
    HOME_ARGS=""
    if [ -d /home/$USER_NAME  ]; then
        # If home dir is a volume from host don't create home
        HOME_ARGS="--no-create-home "
    else
        HOME_ARGS="--create-home "
    fi
    useradd --shell /bin/bash -u $USER_ID -o -c "" $HOME_ARGS $USER_NAME
fi

export HOME=/home/$USER_NAME
GROUP_NAME="host_group"
if [ ! -z $GROUP_ID  ]; then
    if [ $(getent group $GROUP_ID) > /dev/null ]; then
        #If group id exists change name
        OLD_NAME=`getent group $GROUP_ID | cut -d: -f1`
        echo "Changing group name to host's"
        groupmod --new-name $GROUP_NAME $OLD_NAME
    else
        echo "Associating docker group $GROUP_NAME to host's group with GID $GROUP_ID"
        groupadd -g $GROUP_ID $GROUP_NAME
    fi
    usermod -g $GROUP_NAME $USER_NAME
fi

exec /usr/local/bin/gosu $USER_NAME "$cmd"
