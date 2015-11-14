# libpopt-dev & libstdc++ have to be installed
cd

cd peak-linux-driver-7.8/driver ##apply versionnr
make clean
make NET=NO PCI=NO PAR=NO ISA=NO PCC=NO DNG=NO
sudo make install

sudo insmod pcan.ko
