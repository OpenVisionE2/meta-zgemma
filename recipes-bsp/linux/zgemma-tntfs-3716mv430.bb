SUMMARY = "Hardware drivers for TNTFS"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"
require conf/license/license-close.inc

COMPATIBLE_MACHINE = "^(h0|h8)$"

SRCDATE = "20200528"

SRC_URI[md5sum] = "dd43506f34b3e827db951f352c6ed81c"
SRC_URI[sha256sum] = "3a4ffbc520ef7c5dded28b78a99ea58b98c9ebfb500be43f7390033cf67ae867"

SRC_URI = "http://source.mynonpublic.com/tntfs/${HICHIPSET}-tntfs-${SRCDATE}.zip"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

do_compile() {
}

do_populate_sysroot() {
}

do_install() {
    install -d ${D}${nonarch_base_libdir}/modules/${KV}/extra
    install -d ${D}${sysconfdir}/modules-load.d
    install -m 0755 ${S}/tntfs.ko ${D}${nonarch_base_libdir}/modules/${KV}/extra
    echo tntfs >> ${D}${sysconfdir}/modules-load.d/tntfs.conf
}

FILES_${PN} += "${sysconfdir}/modules-load.d/tntfs.conf ${nonarch_base_libdir}/modules/${KV}/extra"
