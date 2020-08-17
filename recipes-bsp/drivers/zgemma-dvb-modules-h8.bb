SRCDATE = "20200727"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"
RDEPENDS_${PN} = "libjpeg-turbo"

require zgemma-dvb-modules.inc

SRC_URI[md5sum] = "1119fe976ec7d0c8731a811c5ae98eca"
SRC_URI[sha256sum] = "4256c92ce24b227586a0afbc0751529b06182a9c3deaec3924ca7246c85ba30f"

COMPATIBLE_MACHINE = "^(h8)$"

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
