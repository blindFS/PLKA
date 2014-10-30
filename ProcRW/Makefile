obj-m := ProcRW.o
KERNELDIR := /usr/lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
MOD := ProcRW.ko

default:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules

install:
	insmod $(MOD)

uninstall:
	rmmod $(MOD)

clean:
	rm -rf *.o *~ core .depend *.order *.symvers .*.cmd *.ko *.mod.c .tmp_versions
