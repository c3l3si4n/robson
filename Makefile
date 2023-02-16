obj-m = robson.o
all:
	make -C ../linux-6.1.8/ M=$(PWD) modules ; cp robson.ko ../initramfs/; cd ../initramfs/; bash build.sh
clean:
	make -C ../linux-6.1.8/ M=$(PWD) clean 
