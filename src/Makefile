.SUFFIXES:

BUILD_DIR:=../$(BUILD_DIR)

TARGET=$(BUILD_DIR)/bloom.a

SOURCES=$(wildcard *.c)

OBJECTS=$(addprefix $(BUILD_DIR)/, $(SOURCES:.c=.o))

all: $(BUILD_DIR) $(TARGET) 

$(BUILD_DIR):   
	mkdir $@

$(TARGET): $(OBJECTS)
	ar rcs $@ $^

$(BUILD_DIR)/%.o: %.c %.h
	$(CC) $(CFLAGS) -c -o $(BUILD_DIR)/$@ $<
