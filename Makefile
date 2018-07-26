CC=g++

target=tablet

ql_dir = QL/
ql_repo = "https://github.com/Dark565/Qer-Library"

CCFlags=-std=c++14 -I$(ql_dir)headers/
LinkerFlags:=

cppfiles=$(wildcard *.cpp)
objects=$(subst main.o,,$(patsubst %.cpp, %.o,$(cppfiles)))

ql_graphics=$(ql_dir)source/QL/Graphics
ql_system=$(ql_dir)source/QL/System

ql_objects=ql-display.o

ql_flags:=

ifeq ($(QL_TYPE),LINKED)
	ql_flags:=-DQL_LIB_LINK
	LinkerFlags:=-lX11 -lXrandr
else
	ql_objects+= ql-library.o ql-module_dynlibs.o
	LinkerFlags:=-ldl
endif

ifeq ($(wildcard $(ql_dir)),)
all: modules
	$(MAKE) build
else
all: build
endif




$(objects):
	$(CC) -c -o $@ $(patsubst %.o, %.cpp, $@) $(CCFlags)

main.o: main.cpp
	$(CC) -c -o $@ $< $(CCFlags) $(ql_flags)

ql-display.o: $(ql_graphics)/display.cpp
	$(CC) -c -o $@ $< $(CCFlags) $(ql_flags)

ql-library.o: $(ql_system)/library.cpp
	$(CC) -c -o $@ $< $(CCFlags) $(ql_flags)

ql-module_dynlibs.o: $(ql_system)/module_dynlibs.cpp
	$(CC) -c -o $@ $< $(CCFlags) $(ql_flags)

build: main.o $(objects) $(ql_objects)
	$(CC) -o $(target) $(objects) $(ql_objects) main.o $(LinkerFlags)

clean:
	rm -rf *.o $(target)

clean_modules:
	rm -rf $(ql_dir)

install:
	install $(target) $(prefix)/usr/bin/

uninstall:
	rm -f $(prefix)/usr/bin/$(target)

modules:
	git clone $(ql_repo) $(ql_dir)

.phony: modules build clean clean_modules install uninstall