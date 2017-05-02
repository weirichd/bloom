.SUFFIXES:

BUILD_DIR:=../$(BUILD_DIR)
TEST_DIR=$(BUILD_DIR)/test
OBJ_DIR=$(TEST_DIR)/objects

TEST_FILE_DIR=$(CURDIR)/files

LIBS=check
LDFLAGS+=`pkg-config --cflags --libs $(LIBS)`

TEST_SOURCE=$(wildcard *.c)
TEST_OBJ=$(addprefix $(OBJ_DIR)/, $(TEST_SOURCE:.c=.o))

PROD_LIBRARY=$(BUILD_DIR)/bloom.a
PROD_HEADER_PATH=../src/

TARGET=$(TEST_DIR)/bloom_test

all: $(BUILD_DIR) $(TEST_DIR) $(OBJ_DIR) $(TARGET)

$(BUILD_DIR) $(TEST_DIR) $(OBJ_DIR):
	mkdir $@

$(TARGET): $(TEST_OBJ) $(PROD_LIBRARY)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS) -lm

$(OBJ_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -D TEST_FILE_DIR="$(TEST_FILE_DIR)" -o $@ $< -I$(PROD_HEADER_PATH)
