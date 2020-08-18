DESCRIPTION = "${MACHINE} Bootargs to extend rootfs"
require conf/license/license-gplv2.inc

PACKAGE_ARCH = "${MACHINE_ARCH}"

SRC_URI = "file://bootargs-mmc.bin \
	file://bootargs-nand.bin \
	file://bootargs-usb.bin \
	"

do_install () {
	install -m 0755 -d ${D}${datadir}
	install -m 0644 ${WORKDIR}/bootargs-usb.bin ${D}${datadir}/
	install -m 0644 ${WORKDIR}/bootargs-nand.bin ${D}${datadir}/
	install -m 0644 ${WORKDIR}/bootargs-mmc.bin ${D}${datadir}/
}

FILES_${PN} = "${datadir}"
