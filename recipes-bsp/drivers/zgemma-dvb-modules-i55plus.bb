SRCDATE = "20201118"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "c577ec40e3172e44ea3dcfa94a438c6b"
SRC_URI[sha256sum] = "c71650d8e3e8c52b89270171b33038b6cfbb6a5339c75f8592c17143445cd19e"

COMPATIBLE_MACHINE = "^(i55plus)$"

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
