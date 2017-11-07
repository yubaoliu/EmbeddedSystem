#!/bin/sh
export QTDIR=/usr/qpe
export QPEDIR=/usr/qpe
export KDEDIR=/usr/qpe
export TSLIB_TSDEVICE=/dev/input/event0
export TSLIB_CONFFILE=/tmp/ts.conf
export TSLIB_CONSOLEDEVICE=none
export TSLIB_CALIBFILE=/tmp/ts-calib.conf
export TSLIB_PLUGINDIR=/usr/qpe/lib
export QT_TSLIBDIR=/usr/qpe/lib/
export LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/qpe/lib/
export QWS_SIZE=640x480
export QWS_MOUSE_PROTO="TPanel:/dev/input/event0 USB"
export LANG=zh_CN
insmod /mnt/yaffs/touchscreen/ts-uptech.o
cp /usr/qpe/etc/ts.conf /tmp
cd /usr/qpe/bin/
if [ "$1" = "c" ]; then
./ts_calibrate
fi

if [ -f "$TSLIB_CALIBFILE" ]; then
./qpe &>/dev/null
else
./ts_calibrate
./qpe &>/dev/null
fi
clear
