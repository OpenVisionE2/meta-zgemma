KV = "4.4.35"
SRCDATE = "20200720"

require zgemma-dvb-modules.inc

SRC_URI[md5sum] = "ab2907291ac594390078373ac1cd1b38"
SRC_URI[sha256sum] = "c4d3ad0935c819e75767d6c54421c5b80c8272de2f36845e12154c811e21ae3a"

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
