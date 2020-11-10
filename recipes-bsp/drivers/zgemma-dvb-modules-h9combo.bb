SRCDATE = "20201104"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "eaa7570ed01fa9954758e4e4e106e71a"
SRC_URI[sha256sum] = "b0bf54e60f6f3aea3844cbbef59e639927936d5b63abf78666c5876b4eb19ffb"

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
