SRCDATE = "20201104"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "2452e2dc3d68f53e62288be6a49469e1"
SRC_URI[sha256sum] = "5a3e1cdfc2a23b3e1bb2966c740e33292de8770e73eb87c3af35d4436b6dbf5a"

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
