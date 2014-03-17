MEMLEAK = memleak.o avltree.o
MEMLEAK_TEST = memleak_test.o

PROGRAMS = \
	memleak_test \

LDFLAGS = -lpthread \
    -lbfd \

CFLAGS = \
	-g -D_GNU_SOURCE -rdynamic \
    -D_LIBBFD \
	
all: $(PROGRAMS)

memleak_test: $(MEMLEAK_TEST) $(MEMLEAK) 
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)
	
clean:
	rm -rf ./*.o $(PROGRAMS) ./*.so
