KV = "4.4.35"
SRCDATE = "20200716"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"
RDEPENDS_${PN} = "libjpeg-turbo"

require zgemma-dvb-modules.inc

SRC_URI[md5sum] = "a3cbeb7f951592ca84d89a49e49d7ed9"
SRC_URI[sha256sum] = "0da57cef839d56f3588d442a40bfd894ec6250e530e4ca3523bfd247b223cf63"

COMPATIBLE_MACHINE = "^(i55plus)$"

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

FILES_${PN} += " ${bindir} ${sysconfdir}/init.d"

