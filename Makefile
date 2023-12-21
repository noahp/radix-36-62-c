.SILENT:

BUILDDIR = build

CFLAGS += \
    -std=c2x \

$(BUILDDIR)/main: $(BUILDDIR)/main.o $(BUILDDIR)/r36_62.o
	gcc $(CFLAGS) -o $@ $^

$(BUILDDIR)/%.o: %.c
	@mkdir -p $(BUILDDIR)
	gcc $(CFLAGS) -c -o $@ $<

.PHONY: test
test: $(BUILDDIR)/main
	rm -f $(BUILDDIR)/expected.txt
	cat test.txt | while read line ; do $< $$line | tee -a $(BUILDDIR)/expected.txt; done
	diff -u0 $(BUILDDIR)/expected.txt expected.txt
	echo "Test passed"

.PHONY: snapshot-update
snapshot-update: $(BUILDDIR)/main
	rm -f expected.txt
	cat test.txt | while read line ; do $< $$line | tee -a expected.txt; done

