SRCDATE = "20201104"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "e12b3e2676b721ee6b76e063e0b348a6"
SRC_URI[sha256sum] = "4eea53b43890283772dedf8949fc1f36df76b632f3e5228a691c3336e698ea4e"

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
