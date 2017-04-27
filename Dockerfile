FROM ubuntu:14.04

RUN apt-get update && apt-get install -y \
   build-essential \
   curl \
   autoconf \
   libtool \
   git \
   valgrind \
   pkg-config

RUN curl -sL https://github.com/libcheck/check/releases/download/0.11.0/check-0.11.0.tar.gz | tar xz

RUN cd check-0.11.0 && autoreconf --install && ./configure && make && make install && cd ..

RUN ldconfig

CMD ["/bin/bash"]
