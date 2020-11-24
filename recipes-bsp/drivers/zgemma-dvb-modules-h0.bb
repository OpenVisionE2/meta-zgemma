SRCDATE = "20201118"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "c5273a14e751fe52125c86deed3436e1"
SRC_URI[sha256sum] = "215f07119f8ddaeb7a992e41721c58d35a3bc73f4ffc5a07c3cfeb55556a8da9"

COMPATIBLE_MACHINE = "^(h0)$"

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
