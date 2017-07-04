#!/bin/sh


rm /home/bogdan/wip/macchina.io/platform/OSP/bundles/com.continental.luama_1.0.0.bndl

rm /home/bogdan/wip/macchina.io/server/bin/Linux/x86_64/codeCache/com.continental.luama*.so
rm /home/bogdan/wip/macchina.io/server/bin/Linux/x86_64/codeCache/hello.lua
rm /home/bogdan/wip/macchina.io/server/bin/Linux/x86_64/codeCache/liblua*


export LD_LIBRARY_PATH=~/wip/macchina.io/platform/lib/Linux/x86_64:~/wip/macchina.io/server/bin/Linux/x86_64/codeCache
cd ./server
bin/Linux/x86_64/macchina 
cd ..

