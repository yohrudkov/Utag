#!/bin/zsh

export PKG_CONFIG_PATH="-L~/.linuxbrew/Cellar/qt/5.15.2/lib/pkgconfig"
export CMAKE_PREFIX_PATH="~/.linuxbrew/Cellar/qt/5.15.2/lib/cmake:$CMAKE_PREFIX_PATH"

cmake . -Bbuild -Wdev -Werror=dev && cmake --build ./build
cp ./build/app/utag ./utag
