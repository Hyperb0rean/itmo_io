obj-m = virt_net_if.o
PWD = $(shell pwd)
ccflags-y := -std=gnu99 -Wno-declaration-after-statement

all:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M="$(PWD)" clean

load:
	sudo insmod virt_net_if.ko

uload:
	sudo rmmod virt_net_if

lcheck:
	@sudo lsmod | grep bl_drv || true