.SUFFIXES:

BUILD_DIR:=../$(BUILD_DIR)
OBJ_DIR:=../$(OBJ_DIR)

TARGET=$(BUILD_DIR)/pybloom.so
C_LIB=$(BUILD_DIR)/libbloom.a

SOURCES=$(wildcard *.c)
OBJECTS=$(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

all: $(TARGET)

$(TARGET): $(OBJECTS) $(C_LIB)
	$(CC) -shared -o $@ $^ `python-config --ldflags`

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -fPIC `python-config --cflags` -I.. -c -o $@ $<
