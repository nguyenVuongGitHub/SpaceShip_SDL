all:
	g++ -I src/include  -L src/lib -o src/main src/*.c -lmingw32 -lSDL2main -lSDL2 -lSDL2_image

# CC=g++
# CFLAGS=-I src/include -I src/include/headers
# LDFLAGS=-L src/lib -lmingw32 -lSDL2main -lSDL2
# SOURCES=src/*.cpp
# EXECUTABLE=src/main

# all: $(EXECUTABLE)

# $(EXECUTABLE): $(SOURCES)
# 	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^

# clean:
# 	rm -f $(EXECUTABLE)
