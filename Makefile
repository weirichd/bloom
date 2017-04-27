SUBDIRS=src test
export BUILD_DIR=build

.PHONY: clean $(SUBDIRS) tags run_tests
.SILENT: clean

export CFLAGS=-std=c99 -Wall -Werror -O3

all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@

clean:
	rm -rf $(BUILD_DIR)

tags: 
	ctags -R --exclude=Makefile

run_tests:	
	./$(BUILD_DIR)/bloom_test
