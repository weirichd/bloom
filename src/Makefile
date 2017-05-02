.SUFFIXES:

export BUILD_DIR:=../$(BUILD_DIR)
export OBJ_DIR=$(BUILD_DIR)/objects

SUB_DIRS=python_bindings

.PHONY: $(SUB_DIRS)

TARGET=$(BUILD_DIR)/libbloom.a
SOURCES=$(wildcard *.c)
OBJECTS=$(addprefix $(OBJ_DIR)/, $(SOURCES:.c=.o))

all: $(BUILD_DIR) $(OBJ_DIR) $(TARGET) $(SUB_DIRS)

$(BUILD_DIR) $(OBJ_DIR):
	mkdir $@

$(SUB_DIRS):
	$(MAKE) -C $@

$(TARGET): $(OBJECTS)
	ar rcs $@ $^

$(OBJ_DIR)/%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $@ $<
