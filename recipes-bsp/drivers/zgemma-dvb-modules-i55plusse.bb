SRCDATE = "20201104"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "83acd93042cdbbb2babf4591058dd20a"                     
SRC_URI[sha256sum] = "a193d1e2718d15443ac6f876c74b0d443af9be6d849298dc038148e32b013c39"

COMPATIBLE_MACHINE = "^(i55plusse)$"

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
