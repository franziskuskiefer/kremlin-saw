
SAW_PATH ?= ../saw-0.4/bin/

all: build run verify

build:
	clang -g -c -emit-llvm -o ct_ops.bc ct_ops.c
	clang -o ct_ops ct_ops.c

run:
	./ct_ops

verify:
	$(SAW_PATH)/saw ct_ops.saw
