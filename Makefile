TOOLCHAIN=${VCPKG_ROOT}/scripts/buildsystems/vcpkg.cmake

all:
	cmake -B cmake-build-release -S . -DCMAKE_TOOLCHAIN_FILE=$(TOOLCHAIN)
	make -C ./cmake-build-release/

run:
	./cmake-build-release/app

clean:
	rm -rf cmake-build-release