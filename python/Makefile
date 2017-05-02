.SUFFIXES:

BUILD_DIR=../build
OBJ_DIR=$(BUILD_DIR)/objects
PYTHON_INLCUDE_PATH=/usr/include/python2.7

TARGET=hash.so

OBJECTS=$(OBJ_DIR)/hash.o pyhash.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $^ `python-config --ldflags`

pyhash.o: pyhash.c
	$(CC) $(CFLAGS) -fPIC `python-config --cflags` -I../src -c -o $@ $<

.PHONY: clean

clean:
	rm $(TARGET) pyhash.o
