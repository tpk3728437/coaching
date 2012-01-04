# Recursive makefile

DIRS = team1

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
