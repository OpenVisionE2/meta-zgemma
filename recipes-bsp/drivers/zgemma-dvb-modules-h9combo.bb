SRCDATE = "20201118"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "810f4ab1e7814c0b104ac077e99a712b"
SRC_URI[sha256sum] = "e003694434a2d5357a318b01b08f200b7eb204f6354c33ceb24e84b3a0548f98"

COMPATIBLE_MACHINE = "^(h9combo)$"

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
