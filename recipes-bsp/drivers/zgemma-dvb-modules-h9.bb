SRCDATE = "20201118"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "c37f50c9c88bb808a9e8967f231ec031"
SRC_URI[sha256sum] = "4e18ec799c375707caa4ae43f9cbe735f0139cae189d0151dcf4706c1abe53cf"

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
