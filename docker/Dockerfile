FROM ros:melodic

ARG USER

RUN apt-get update && apt-get install -y sudo vim ack
RUN apt-get update && apt-get install -y terminator bash-completion python-catkin-tools gdb clang-format-4.0
RUN apt-get update && apt-get install -y ros-melodic-catkin ros-melodic-resource-retriever
RUN apt-get update && apt-get install -y liburdfdom-dev

RUN gpg --keyserver hkp://p80.pool.sks-keyservers.net:80 --recv-keys B42F6819007F00F88E364FD4036A9C25BF357DD4
RUN curl -k -o /usr/local/bin/gosu -SL "https://github.com/tianon/gosu/releases/download/1.10/gosu-$(dpkg --print-architecture)" \
    && curl -k -o /usr/local/bin/gosu.asc -SL "https://github.com/tianon/gosu/releases/download/1.10/gosu-$(dpkg --print-architecture).asc" \
    && gpg --verify /usr/local/bin/gosu.asc \
    && rm /usr/local/bin/gosu.asc \
    && chmod +x /usr/local/bin/gosu


RUN echo "root:palroot" | chpasswd
RUN useradd --shell /bin/bash -c "" --create-home user
RUN adduser user video
RUN adduser user audio
# Give sudo access to user "user"
RUN echo "user ALL=(ALL) NOPASSWD: ALL" >> /etc/sudoers
COPY gosu_entrypoint.sh /usr/local/bin/gosu_entrypoint.sh
ENTRYPOINT ["/usr/local/bin/gosu_entrypoint.sh"]

