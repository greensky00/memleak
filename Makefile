MEMLEAK = memleak.o rbwrap.o rbtree.o
MEMLEAK_TEST = memleak_test.o

PROGRAMS = \
	memleak_test \

LDFLAGS =
CFLAGS = \
	-g -D_GNU_SOURCE \
	
all: $(PROGRAMS)

memleak_test: $(MEMLEAK_TEST) $(MEMLEAK) 
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	
clean:
	rm -rf ./*.o $(PROGRAMS) ./*.so
