FROM ubuntu:20.04
WORKDIR /home/
RUN apt-get --yes update
RUN apt-get --yes install gcc git
RUN git clone https://github.com/saliei/DirectGrav.git
