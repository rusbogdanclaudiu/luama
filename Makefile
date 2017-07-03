


.PHONY: .lua all clean
.lua:
	@echo "compiling lua"
	$(MAKE) linux -C ./src/lua

all: .lua
	$(MAKE) -f ./Makefile-bundle

clean: 
	$(MAKE) clean -C ./src/lua
	$(MAKE) clean -f ./Makefile-bundle
	rm -rf ./obj
	rm -rf ./bin
	rm -rf ./bundles
