SRCDATE = "20201104"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"
RDEPENDS_${PN} = "libjpeg-turbo"

require zgemma-dvb-himodules.inc

SRC_URI[md5sum] = "362765e31e7c566b584e95b11cfcfe8f"
SRC_URI[sha256sum] = "7667d973cd171d0824fc569b0d1bcaa69e842c99f95cfef0142f2fafbe9b8b45"

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
