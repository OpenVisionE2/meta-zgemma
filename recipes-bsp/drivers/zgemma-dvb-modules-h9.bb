KV = "4.4.35"
SRCDATE = "20200513"

PROVIDES = "virtual/blindscan-dvbc virtual/blindscan-dvbs"

require zgemma-dvb-modules.inc

SRC_URI = "http://source.mynonpublic.com/zgemma/${MACHINE}-drivers-${KV}-${SRCDATE}.zip"

SRC_URI[arm.md5sum] = "4cedacb60a95353ad57a71111ec7dbdb"
SRC_URI[arm.sha256sum] = "ee415c6902625f6a89c110386e27c7b619448bbf9a6d84f66d8322f4d3264be6"
SRC_URI[md5sum] = "4cedacb60a95353ad57a71111ec7dbdb"
SRC_URI[sha256sum] = "ee415c6902625f6a89c110386e27c7b619448bbf9a6d84f66d8322f4d3264be6"

COMPATIBLE_MACHINE = "^(h9)$"

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

