SRCDATE = "20201118"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "4a548841c8546463dd22705b6c8c1609"
SRC_URI[sha256sum] = "bed8bba7e60c4ac74e29529a15715276f95302f8d9b09ee5fabcdf02d7ae9c9b"

COMPATIBLE_MACHINE = "^(h9se)$"

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
