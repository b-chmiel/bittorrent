.PHONY: build test

build:
	CXX=clang++ cmake . -GNinja -DCMAKE_LINKER=/usr/bin/lld -B ./build && cmake --build ./build

test: build
	cd build/test &&  ./test -i -p -l all

clean:
	rm -rf build