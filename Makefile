CC=g++

CCFlags=-O2 -std=c++14

objects=$(patsubst %.cpp, %.o,$(wildcard *.cpp))

target=tconf

all: build

$(objects):
	$(CC) -c -o $@ $(patsubst %.o, %.cpp, $@) $(CCFlags)

build: $(objects)
	$(CC) -o $(target) $(objects)

clean:
	rm -rf $(objects)

install:
	install $(target) $(prefix)/usr/bin/

.phony: build clean install