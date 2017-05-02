.SUFFIXES:

BUILD_DIR=../build
OBJ_DIR=$(BUILD_DIR)/objects
PYTHON_INLCUDE_PATH=/usr/include/python2.7

TARGET=hash.so

OBJECTS=$(OBJ_DIR)/hash.o pyhash.o

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) -shared -o $@ $^ -lpython

pyhash.o: pyhash.c
	$(CC) $(CFLAGS) -I$(PYTHON_INLCUDE_PATH) -I../src -c -o $@ $<
