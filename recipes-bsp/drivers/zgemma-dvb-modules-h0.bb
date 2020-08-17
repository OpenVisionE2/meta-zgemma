SRCDATE = "20200727"

require zgemma-dvb-modules.inc

SRC_URI[md5sum] = "e9c6357985081d4fcada29da100e9469"
SRC_URI[sha256sum] = "3e7cdb6ef627d7d71234c94e37ee4d7574b5faf02d0e720126f9963f246fbf9c"

COMPATIBLE_MACHINE = "^(h0)$"

INITSCRIPT_NAME = "suspend"
INITSCRIPT_PARAMS = "start 89 0 ."
inherit update-rc.d

do_configure[noexec] = "1"

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

do_install_append() {
	install -d ${D}${sysconfdir}/init.d
	install -d ${D}${bindir}
	install -m 0755 ${S}/suspend ${D}${sysconfdir}/init.d
	install -m 0755 ${S}/turnoff_power ${D}${bindir}
}

do_package_qa() {
}

FILES_${PN} += "${bindir} ${sysconfdir}/init.d"
