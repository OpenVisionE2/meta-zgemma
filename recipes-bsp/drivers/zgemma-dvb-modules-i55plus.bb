SRCDATE = "20201104"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "84b99b8d6886817d268acb31dddb2959"
SRC_URI[sha256sum] = "596940343eaada6257e91d9bdc7af6102e4b92ffc5c461b7f436967e8094432d"

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
