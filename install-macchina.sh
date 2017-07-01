#!/bin/sh

git clone https://github.com/macchina-io/macchina.io.git
cd macchina.io
git checkout master
make -s -j8 DEFAULT_TARGET=shared_release

