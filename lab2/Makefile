obj-m = block_drv_4_15.o
PWD = $(shell pwd)
ccflags-y := -std=gnu99 -Wno-declaration-after-statement

all:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" clean

load:
	sudo insmod block_drv_4_15.ko    

uload:
	sudo rmmod block_drv_4_15

lcheck:
	@sudo lsmod | grep block_drv_4_15 || true