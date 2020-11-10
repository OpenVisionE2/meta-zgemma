SRCDATE = "20201104"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "a70eff5bf6c4f44e2a067cbaae987ac3"
SRC_URI[sha256sum] = "0f827175f687611e65bc035aeba4ae18cb8afd6f9d18a6a05c4e6b0941b0f39f"

COMPATIBLE_MACHINE = "^(h9)$"

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
