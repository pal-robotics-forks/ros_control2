FROM ros:melodic

RUN apt-get update && apt-get install -y sudo vim ack
RUN apt-get update && apt-get install -y ros-melodic-catkin ros-melodic-resource-retriever ros-melodic-ros-control*
RUN useradd -rm -d /home/bence -s /bin/bash -g root -G sudo bence
RUN echo '%sudo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

USER bence
RUN mkdir -p /home/bence/ws
RUN echo "source /opt/ros/melodic/setup.bash" >> /home/bence/.bashrc
