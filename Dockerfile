FROM ubuntu:24.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    pkg-config \
    git \
    libseccomp-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

USER ${UID}:${GID}

WORKDIR /workspace

CMD ["/bin/bash"]
