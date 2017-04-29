.SUFFIXES:

BUILD_DIR:=../$(BUILD_DIR)
OBJ_DIR=$(BUILD_DIR)/objects

TARGET=$(BUILD_DIR)/bloom.a

SOURCES=$(wildcard *.c)

OBJECTS=$(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

all: $(BUILD_DIR) $(OBJ_DIR) $(TARGET)

$(BUILD_DIR) $(OBJ_DIR):
	mkdir $@

$(TARGET): $(OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
