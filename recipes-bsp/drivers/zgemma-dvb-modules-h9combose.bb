SRCDATE = "20201118"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "b990c1ae716fa42e27e649fc80eb17a8"
SRC_URI[sha256sum] = "1e79ad29361c248cbd3043d1786348ef9713bf3baa65839affe076fae1a44820"

COMPATIBLE_MACHINE = "^(h9combose)$"

# Generate a simplistic standard init script
do_compile_append () {
	cat > suspend << EOF
#!/bin/sh

runlevel=runlevel | cut -d' ' -f2

if [ "\$runlevel" != "0" ] ; then
	exit 0
fi

mount -t sysfs sys /sys

${bindir}/turnoff_power
EOF
}
