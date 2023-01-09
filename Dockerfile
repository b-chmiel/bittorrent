FROM debian
RUN apt-get update && \
	export DEBIAN_FRONTEND=noninteractive && \
	apt-get install -y \
	cmake \
	clang \
	ninja-build \
	git \
	libboost-all-dev \
	libdw-dev \
	binutils-dev

WORKDIR /tmp
RUN git clone --depth 1 https://github.com/bombela/backward-cpp && \
	cd backward-cpp && \
	mkdir build && \
	cd build && \
	cmake .. && \
	make install

WORKDIR /app
COPY . .
CMD ["/bin/bash"]