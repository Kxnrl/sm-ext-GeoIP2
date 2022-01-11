#!/bin/bash

sudo apt-get update
sudo apt-get install -y gcc-multilib g++-multilib

set -e

EXT_DIR=$(pwd)

#git fetch --unshallow
git fetch --depth=10000
export GITCOMMIT=$(git rev-list --count HEAD)

#clone ambuild
echo "Installing ambuild ..."
git clone https://github.com/alliedmodders/ambuild $HOME/ambuild
pushd $HOME/ambuild
sudo python setup.py install
popd

#clone sourcemod / metamod / hl2sdk
echo "Installing Sourcemod/Metamod/HL2SDK ..."
git clone https://github.com/alliedmodders/sourcemod --recursive --branch $SMBRANCH --single-branch "$EXT_DIR/sourcemod"

#build
mkdir -p "$EXT_DIR/build"
pushd "$EXT_DIR/build"
export CC=clang-10;export CXX=clang++-10;
python "$EXT_DIR/configure.py" --enable-optimize --sm-path "$EXT_DIR/sourcemod" --targets=x86
ambuild
popd
