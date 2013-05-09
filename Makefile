CC=gcc
CFLAGS=-c -Wall
LDFLAGS=
SOURCES=cbuffer.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=start

all: $(SOURCES) $(EXECUTABLE)
	
$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm $(OBJECTS) $(EXECUTABLE) 
