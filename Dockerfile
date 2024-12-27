FROM ubuntu:22.04
RUN apt-get update && apt-get install -y \
    build-essential \
	tmux \
    gcc \
    gdb \
    valgrind \
    make \
    vim \
    git \
    && apt-get clean
WORKDIR /app