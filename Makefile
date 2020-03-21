SYSCONF_LINK = gcc
CPPFLAGS     =
LDFLAGS      =
OUT_PUT_IMAGE = output.png

DESTDIR = ./
TARGET  = main

OBJECTS := $(patsubst %.c,%.o,$(wildcard *.c))

all: $(DESTDIR)$(TARGET)

$(DESTDIR)$(TARGET): $(OBJECTS)
	$(SYSCONF_LINK) -Wall $(LDFLAGS) -o $(DESTDIR)$(TARGET) $(OBJECTS)

$(OBJECTS): %.o: %.c
	$(SYSCONF_LINK) -Wall $(CPPFLAGS) -c $(CFLAGS) $< -o $@

dev: clean all
	-$(DESTDIR)$(TARGET)
	-open $(DESTDIR)$(OUT_PUT_IMAGE)

clean:
	-rm -f $(OBJECTS)
	-rm -f $(TARGET)
	-rm -f *.png

