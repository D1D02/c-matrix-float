CC := gcc
CFLAGS := -Wall -Wextra -o3

TARGET := example

SOURCES := example.c matrix.c
HEADERS := matrix.h

OBJECTS := $(SOURCES:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	@echo "Linking files..."
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	@echo "Compiling $<..."
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET) $(OBJECTS)
