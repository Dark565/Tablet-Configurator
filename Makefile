CC=g++

target=tablet

ewl_dir = EWL
ewl_repo = "https://github.com/Dark565/EWL.git"

CCFlags=-std=c++14 -I$(ewl_dir)/headers/
LinkerFlags:=

cppfiles=$(wildcard *.cpp)
objects=$(subst main.o,,$(patsubst %.cpp, %.o,$(cppfiles)))

ewl_graphics=$(ewl_dir)/source/EWL/Graphics
ewl_system=$(ewl_dir)/source/EWL/System

ewl_objects=ewl-display.o

ewl_flags:=

ifeq ($(EWL_TYPE),LINKED)
	ewl_flags:=-DEWL_LIB_LINK
	LinkerFlags:=-lX11 -lXrandr
else
	ewl_objects+= ewl-library.o ewl-global_dynlibs.o
	LinkerFlags:=-ldl
endif

ifeq ($(wildcard $(ewl_dir)),)
all: modules
	$(MAKE) build
else
all: build
endif


$(objects):
	$(CC) -c -o $@ $(patsubst %.o, %.cpp, $@) $(CCFlags)

main.o: main.cpp
	$(CC) -c -o $@ $< $(CCFlags) $(ewl_flags)

ewl-display.o: $(ewl_graphics)/display.cpp
	$(CC) -c -o $@ $< $(CCFlags) $(ewl_flags)

ewl-library.o: $(ewl_system)/library.cpp
	$(CC) -c -o $@ $< $(CCFlags) $(ewl_flags)

ewl-global_dynlibs.o: $(ewl_system)/global_dynlibs.cpp
	$(CC) -c -o $@ $< $(CCFlags) $(ewl_flags)

build: main.o $(objects) $(ewl_objects)
	$(CC) -o $(target) $(objects) $(ewl_objects) main.o $(LinkerFlags)

clean:
	rm -rf *.o $(target)

clean_modules:
	rm -rf $(ewl_dir)

install:
	install $(target) $(prefix)/usr/bin/

uninstall:
	rm -f $(prefix)/usr/bin/$(target)

modules:
	git clone $(ewl_repo) $(ewl_dir)

.phony: modules build clean clean_modules install uninstall
