CC=g++

target=tconf

ql_dir = QL/
ql_repo = "https://github.com/Dark565/Qer-Library"

CCFlags=-std=c++14 -I$(ql_dir)headers/
LinkerFlags=-lX11 -lXrandr

cppfiles=$(wildcard *.cpp)
objects=$(patsubst %.cpp, %.o,$(cppfiles))

ql_graphics=$(ql_dir)source/QL/Interface/Graphics
ql_source=$(ql_graphics)/Display

ql_objects=ql-display.o

all: modules build

$(objects):
	$(CC) -c -o $@ $(patsubst %.o, %.cpp, $@) $(CCFlags)

ql-display.o: $(ql_source)/display.cpp
	$(CC) -c -o $@ $< $(CCFlags)

build: $(objects) $(ql_objects)
	$(CC) -o $(target) $(objects) $(ql_objects) $(LinkerFlags)

clean:
	rm -rf *.o

clean_modules:
	rm -rf $(ql_dir)

install:
	install $(target) $(prefix)/usr/bin/

uninstall:
	rm -f $(prefix)/usr/bin/$(target)

modules:
ifeq ($(wildcard $(ql_dir)),)
	git clone $(ql_repo) $(ql_dir)
endif

.phony: modules build clean clean_modules install uninstall