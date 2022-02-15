.PHONY: build test

build:
	CXX=clang++ cmake . -G"Unix Makefiles" -DCMAKE_LINKER=/usr/bin/lld -DCMAKE_BUILD_TYPE=Debug -B ./build && cmake --build ./build

test: build
	cd build/test &&  ./test -i -p -l all

clean:
	rm -rf build