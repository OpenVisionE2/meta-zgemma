
# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

IMAGE_CLASSES += "zgemma-emmc_image_multiboot"
IMAGE_FSTYPES += "zgemmc tar"
IMAGE_ROOTFS_SIZE ?= "294912"

SOC_FAMILY = "bcm7251s"
RCTYPE = "21"

MTD_BOOTFS = "mmcblk0p1"
MTD_ROOTFS = "mmcblk0p3"
MTD_KERNEL = "mmcblk0p2"
KERNEL_FILE = "kernel.bin"
ROOTFS_FILE = "rootfs.tar.bz2"
MTD_BLACK  = "mmcblk0"

#Provider
PREFERRED_PROVIDER_virtual/kernel = "linux-zgemma"
PREFERRED_VERSION_linux-zgemma = "4.10.12"
PREFERRED_PROVIDER_virtual/egl ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgbm ?= "zgemma-v3ddriver-${MACHINE}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"
PREFERRED_PROVIDER_virtual/blindscan-dvbc = "zgemma-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "zgemma-dvb-modules-${MACHINE}"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/zgemma-essential.inc

MACHINE_EXTRA_RRECOMMENDS += "\
	gstreamer1.0-plugin-dvbmediasink \
	${@bb.utils.contains('MACHINE_FEATURES', 'swap', 'zgemma-swapcreate', '',d)} \
	"

DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-vb9 --with-wma --with-wmv --with-pcm --with-dts --with-eac3"

MACHINE_FEATURES += "alsa usbhost switchoff osdposition hdmicec blindscan-tbs textlcd 7segment dvb-c v3d-nxpl emmc ci mountboot blindscan-dvbs swap AV_JACK HDMI"

IMAGE_CMD_zgemmc_append = "\
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}.emmc.img ${IMGDEPLOYDIR}/${IMAGEDIR}/disk.img; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	cp ${DEPLOY_DIR_IMAGE}/zImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${KERNEL_FILE}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${IMGDEPLOYDIR}/${IMAGEDIR}/rootfs.tar; \
	rm -f ${IMGDEPLOYDIR}/*.zip; \
	cd ${IMGDEPLOYDIR}; \
	zip ${IMAGE_NAME}_recovery_emmc.zip ${IMAGEDIR}/disk.img ${IMAGEDIR}/imageversion; \
	zip ${IMAGE_NAME}_usb.zip ${IMAGEDIR}/imageversion ${IMAGEDIR}/${KERNEL_FILE} ${IMAGEDIR}/${ROOTFS_FILE}; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.tar.bz2; \
	rm -Rf ${IMAGEDIR}; \
"
