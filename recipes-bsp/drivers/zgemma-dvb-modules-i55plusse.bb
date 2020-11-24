SRCDATE = "20201118"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "8c1f6b4a3dfe8fd64bba6cbbe4b9b263"                     
SRC_URI[sha256sum] = "643aba19bb1ec3bd359207423c386e40c5ae9a167189d3236c87c3bdb8d59e71"

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
