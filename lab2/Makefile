obj-m = block_drv.o
PWD = $(shell pwd)
ccflags-y := -std=gnu99 -Wno-declaration-after-statement

all:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" clean

load:
	sudo insmod block_drv.ko    

uload:
	sudo rmmod block_drv

lcheck:
	@sudo lsmod | grep block_drv || true