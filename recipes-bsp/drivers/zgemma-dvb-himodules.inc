DESCRIPTION = "Hardware drivers for ${MACHINE}"
SECTION = "base"
PRIORITY = "required"
LICENSE = "CLOSED"

PACKAGE_ARCH = "${MACHINE_ARCH}"

PV = "${KV}-${SRCDATE}"

SRC_URI = "http://www.zgemma.org/downloads/${MACHINETYPE}-drivers-${PV}.zip;name=${ARCH}"

S = "${WORKDIR}"

INHIBIT_PACKAGE_STRIP = "1"

inherit module

FILES_${PN} += "${sysconfdir}/modprobe.d/${MACHINE}.conf ${nonarch_base_libdir}/modules/${KV}/extra"

do_compile() {
}

do_install() {
	install -d ${D}${nonarch_base_libdir}/modules/${KV}/extra
	install -d ${D}${sysconfdir}/modprobe.d
	install -m 0755 ${S}/*.ko ${D}${nonarch_base_libdir}/modules/${KV}/extra
	for i in ${MACHINETYPE}_1 ${MACHINETYPE}_2 ${MACHINETYPE}_3 ${MACHINETYPE}_4; do
		echo blacklist $i >> ${D}${sysconfdir}/modprobe.d/${MACHINE}.conf
	done
}

pkg_prerm_${PN}() {
	if [ "x$D" == "x" ]; then
		if [ -f ${nonarch_base_libdir}/modules/${KV}/extra/hi_play.ko ] ; then
			rm -f ${nonarch_base_libdir}/modules/${KV}/extra/hi_play.ko;
		fi
	fi
}
