# Recursive makefile

DIRS = src

all:
	for d in $(DIRS); \
	do                               \
		$(MAKE) --directory=$$d;       \
	done

clean:
	for d in $(DIRS); \
	do                               \
		$(MAKE) --directory=$$d clean;       \
	done

test:
	for d in $(DIRS); \
	do                               \
		cd $$d; $(MAKE) test; cd .. done; \
	done

valgrind:
	for d in $(DIRS); \
	do                               \
		cd $$d; $(MAKE) valgrind; cd .. done; \
	done
