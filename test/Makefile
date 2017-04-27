.SUFFIXES:

BUILD_DIR:=../$(BUILD_DIR)

LIBS=check
LDFLAGS+=`pkg-config --cflags --libs $(LIBS)`

TEST_SOURCE=bloom_test.c
TEST_OBJ=$(addprefix $(BUILD_DIR)/, $(TEST_SOURCE:.c=.o))

PROD_LIBRARY=$(BUILD_DIR)/bloom.a

TARGET=$(BUILD_DIR)/bloom_test

all: $(TARGET)

$(TARGET): $(TEST_OBJ) $(PROD_LIBRARY)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

$(BUILD_DIR)/%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<
