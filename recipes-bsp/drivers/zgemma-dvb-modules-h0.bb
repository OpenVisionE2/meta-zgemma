SRCDATE = "20201104"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "0e583118804b75dfbecaa74f68e56225"
SRC_URI[sha256sum] = "b61d8930570acd6a668cb36fd8feb8a001fcb8b39ad056785c531b4805dde3c0"

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
