.PHONY: build test

build: configure
	cmake --build ./build --target main

buildTest: configure
	cmake --build ./build --target unit_test

configure:
	CXX=clang++ cmake . -G"Ninja" -DCMAKE_LINKER=/usr/bin/lld -DCMAKE_BUILD_TYPE=Debug -B ./build

test: buildTest
	cd build && ninja check

unit_test: buildTest
	cd build/test &&  ./unit_test -i -p 

clean:
	rm -rf build