# main compiler
CC := gcc

CFLAGS=-c -Wall

LDFLAGS := -s

# Here is a simple Make Macro.
TARGET = main
SRCDIR = src
DEPDIR = dep
OBJDIR = obj

SOURCES := $(wildcard $(SRCDIR)/*.c) \
			$(wildcard $(SRCDIR)/*/*.c) \
			$(wildcard $(SRCDIR)/*/*/*.c)
SRCDIRS := $(sort $(dir $(SOURCES)))

DEPENDS := $(subst $(SRCDIR),$(DEPDIR),$(SOURCES))
DEPENDS := $(DEPENDS:.c=.d)
DEPDIRS := $(sort $(dir $(DEPENDS)))

OBJECTS := $(subst $(SRCDIR),$(OBJDIR),$(SOURCES))
OBJECTS := $(OBJECTS:.c=.o)
OBJDIRS := $(sort $(dir $(OBJECTS)))


.PHONY : all create_dirs depend clean

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(LD) $(LDFLAGS) -o $@ $(OBJECTS)

$(OBJECTS): create_dirs depend

	
create_dirs:
	mkdir -p $(DEPDIR) $(OBJDIR)
	for i in $(DEPDIRS); do mkdir -p $$i; done
	for i in $(OBJDIRS); do mkdir -p $$i; done

depend:
	$(CC) -M $(CFLAGS) $(SOURCES) > dependences

-include dependences

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -c -o $@

clean:
	rm -f .depend *.o
