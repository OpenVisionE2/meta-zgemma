SRCDATE = "20201118"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "da99936ca67e851f754e580eb3703252"
SRC_URI[sha256sum] = "766c97809e3ccfbd7d4f9e57c91797ee1b6c518ff4d9b0016049b6948d66fc1f"

COMPATIBLE_MACHINE = "^(h8)$"

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
