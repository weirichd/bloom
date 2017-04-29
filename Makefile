SUBDIRS=src test
export BUILD_DIR=build

VALGRIND_FLAGS=--leak-check=full

.PHONY: clean $(SUBDIRS) tags run_tests
.SILENT: clean

export CFLAGS=-std=c99 -Wall -Werror -O3 -g

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	rm -rf $(BUILD_DIR)

tags: 
	ctags -R --exclude=Makefile

run_tests:	
	./$(BUILD_DIR)/bloom_test

mem_test:
	CK_FORK=no valgrind $(VALGRIND_FLAGS) ./$(BUILD_DIR)/bloom_test
