SYSCONF_LINK = gcc
OUT_PUT_IMAGE = output.png

DESTDIR = ./
TARGET  = main

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall -o $(DESTDIR)$(TARGET) $(OBJECTS)

$(OBJECTS): %.o: %.c
	$(SYSCONF_LINK) -Wall -c $(CFLAGS) $< -o $@

test: all
	time $(DESTDIR)$(TARGET)

dev: clean all
	-$(DESTDIR)$(TARGET)
	-open $(DESTDIR)$(OUT_PUT_IMAGE)

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.png

