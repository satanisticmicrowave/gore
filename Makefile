### Copyright 2025-02-15 07:02:28 satanisticmicrowave. All rights reserved.
###
### Author: satanisticmicrowave <satanisticmicrowave@ya.ru>
### Date: 2025-02-15 07:02:28
### File: Makefile
###
### Made with love :3

.ONESHELL:

._mk-build:
	$(MAKE) clean
	mkdir -p build

._build:
	cmake -B build -S . -DCMAKE_PROJECT_TOP_LEVEL_INCLUDES=conan_provider.cmake -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -DCMAKE_BUILD_TYPE=$(_BUILD_TYPE)
	cmake --build build --config $(_BUILD_TYPE)

build-debug:
	$(MAKE) ._mk-build
	export _BUILD_TYPE=Debug
	$(MAKE) ._build


build-release:
	$(MAKE) ._mk-build
	export _BUILD_TYPE=Release
	$(MAKE) ._build
	
install:
	cd build && sudo make install

clean:
	rm -rf build
	sudo rm -rf /usr/local/lib64/libgore*
	sudo rm -rf /usr/local/include/gore
