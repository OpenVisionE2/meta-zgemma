SRCDATE = "20201118"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "3e4b5caa71c59e5603c8b0958b892664"
SRC_URI[sha256sum] = "ec13edd7620623c6747bfac7f6f133fdd9725d533c303b6f7c927fa8634515bf"

COMPATIBLE_MACHINE = "^(h10)$"

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
