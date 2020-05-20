KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-zgemma"
PREFERRED_VERSION_linux-zgemma = "4.10.12"
PREFERRED_PROVIDER_virtual/egl ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgbm ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"
PREFERRED_PROVIDER_virtual/blindscan-dvbc ?= "zgemma-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs ?= "zgemma-dvb-modules-${MACHINE}"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/zgemma-essential.inc

MACHINE_EXTRA_RRECOMMENDS += "\
	gstreamer1.0-plugin-dvbmediasink \
	ntfs-3g \
	"

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

MACHINE_FEATURES += "alsa usbhost wlan 3dtv switchoff osdposition hdmicec blindscan-tbs"

IMAGEDIR ?= "zgemma/${MACHINE}"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_zgemmc_append = "\
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.emmc.img ${IMGDEPLOYDIR}/${IMAGEDIR}/disk.img; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	cp ${DEPLOY_DIR_IMAGE}/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/kernel.bin; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	rm -f ${IMGDEPLOYDIR}/*.zip; \
	cd ${IMGDEPLOYDIR}; \
	zip ${IMAGE_NAME}_recovery_emmc.zip ${IMAGEDIR}/disk.img ${IMAGEDIR}/imageversion; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/imageversion ${IMAGEDIR}/kernel.bin ${IMAGEDIR}/rootfs.tar.bz2; \
	rm -Rf ${IMAGEDIR}; \
"
