FROM python:2.7

RUN apt-get update && apt-get install -y \
   build-essential \
   curl \
   autoconf \
   libtool \
   git \
   valgrind \
   pkg-config \
   python-dev \
   wamerican

RUN curl -sL https://github.com/libcheck/check/releases/download/0.11.0/check-0.11.0.tar.gz | tar xz

RUN cd check-0.11.0 && autoreconf --install && ./configure && make && make install

RUN ldconfig

RUN pip install numpy
RUN pip install scipy

CMD ["/bin/bash"]
