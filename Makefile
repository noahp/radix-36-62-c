.SILENT:

BUILDDIR = build

CFLAGS += \
    -Wall \
    -Wextra \
    -Werror \
    -fstack-protector-strong \
    -fstack-clash-protection \
    -fstack-protector-all \
    -ftrapv \
    --coverage \
    -O2 \
    -g \
    -std=c2x \

ifeq (1,$(ENABLE_ASAN))
    CFLAGS += \
        -fsanitize=address \
        -fsanitize=undefined \
        -fno-sanitize-recover=all \

endif

# some additional flags if clang is the compiler
ifneq (,$(findstring clang,$(shell $(CC) --version)))
    CFLAGS += \
        -Weverything \
        -Wno-declaration-after-statement \

GCOV_TOOL ?= ./llvm-cov-wrapper.sh

endif

$(BUILDDIR)/main: $(BUILDDIR)/main.o $(BUILDDIR)/r36_62.o
	echo "Linking $@"
	$(CC) $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: %.c
	echo "Compiling $@"
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) -c -o $@ $<

GCOV_TOOL ?= gcov

.PHONY: test
test: $(BUILDDIR)/main
	rm -f $(BUILDDIR)/expected.txt
	cat test.txt | while read line ; do $< $$line | tee -a $(BUILDDIR)/expected.txt; done
	diff -u0 $(BUILDDIR)/expected.txt expected.txt
	echo "\n=== Test passed ==="
# generate lcov report
	lcov --gcov-tool $(GCOV_TOOL) --capture --directory . --no-external --output-file $(BUILDDIR)/coverage.info
# filter out main.c. on lcov 2 we can use 'genhtml --exclude main.c' instead 🥲
	lcov --gcov-tool $(GCOV_TOOL) --remove $(BUILDDIR)/coverage.info '*main.c' --output-file $(BUILDDIR)/coverage.info
	genhtml $(BUILDDIR)/coverage.info --dark-mode --output-directory $(BUILDDIR)/coverage
	echo "\n=== Coverage report ==="
	echo "See file://$(PWD)/$(BUILDDIR)/coverage/index.html"

.PHONY: snapshot-update
snapshot-update: $(BUILDDIR)/main
	rm -f expected.txt
	cat test.txt | while read line ; do $< $$line | tee -a expected.txt; done

.PHONY: clean
clean:
	rm -rf $(BUILDDIR)
