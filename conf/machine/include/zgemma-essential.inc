DISTRO_FEATURES_remove += "x11 wayland directfb"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	zgemma-dvb-modules-${MACHINE} \
	${@bb.utils.contains("MACHINE_FEATURES", "emmc", "zgemma-resizerootfs partitions-by-name" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "bluetooth", "kernel-module-btusb bluez5" , "", d)} \
	"

BOX_BRAND = "airdigital"

IMAGEDIR ?= "zgemma/${MACHINE}"

RCNAME ?= "zgemma3"
RCIDNUM ?= "1"
