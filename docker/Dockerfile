FROM ros:melodic

ARG USER

RUN apt-get update && apt-get install -y sudo vim ack
RUN apt-get update && apt-get install -y ros-melodic-catkin ros-melodic-resource-retriever ros-melodic-ros-control*

RUN useradd -rm -d /home/$USER -s /bin/bash -g root -G sudo $USER
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER $USER
RUN mkdir -p /home/$USER/ws
RUN echo "source /opt/ros/melodic/setup.bash" >> /home/$USER/.bashrc
