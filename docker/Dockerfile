FROM ubuntu:18.04
MAINTAINER Container_Club
ENV TERM="xterm" COLUMNS="200" LINES="50"
COPY ./ /root/
RUN apt-get update -y && apt-get install libcurl4-openssl-dev curl libsan* make g++ -y && cd /root && wget ftp://ftp.gnu.org/gnu/ncurses/ncurses-6.1.tar.gz && tar xvf ncurses-6.1.tar.gz && cd ncurses-6.1 && ./configure && make && make install
WORKDIR /root
CMD /root/apple/a.out
