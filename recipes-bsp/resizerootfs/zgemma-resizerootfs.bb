DESCRIPTION = "Zgemma resize rootfs"
require conf/license/license-gplv2.inc

COMPATIBLE_MACHINE = "^(h7|h9|h9combo|h10|i55plus|h9combose|h9se|i55plusse|i55plusse)$"

RDEPENDS_${PN} = "e2fsprogs-resize2fs"

SRC_URI = "file://resizerootfs"

inherit update-rc.d

INITSCRIPT_NAME = "resizerootfs"
INITSCRIPT_PARAMS = "start 7 S ."

do_install () {
    install -m 0755 -d ${D}${sysconfdir}/init.d
    install -m 0755 ${WORKDIR}/resizerootfs ${D}${sysconfdir}/init.d/resizerootfs
}
