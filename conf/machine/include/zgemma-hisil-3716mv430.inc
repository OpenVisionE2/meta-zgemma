DISTRO_FEATURES_remove = "x11 directfb"

KERNEL_MODULE_AUTOLOAD += "xfs"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED = "rtc"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa7thf"

SOC_FAMILY = "hisi3716mv430"
HICHIPSET = "3716mv430"
CHIPSET = "Hi3716Mv430"

IMAGE_CLASSES += " zgemma-ubi_image"
IMAGE_FSTYPES += " ubi zgemmaubi"

MKUBIFS_ARGS = "-m 2048 -e 126976 -c 4096"
UBINIZE_ARGS = "-m 2048 -p 128KiB"

UBI_VOLNAME = "rootfs"
CMDLINE ?= "console=ttyAMA0,115200n8"

MTD_KERNEL = "mtd9"
MTD_ROOTFS = "mtd10"
KERNEL_FILE = "uImage"
ROOTFS_FILE = "rootfs.ubi"

RCTYPE = "25"


#Provider
PREFERRED_PROVIDER_virtual/kernel ?= "linux-zgemma"
PREFERRED_VERSION_linux-zgemma = "4.4.35"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink ?= "gstreamer1.0-plugin-dvbmediasink"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice ?= "enigma2-plugin-systemplugins-servicehisilicon"

require conf/machine/include/tune-cortexa7.inc
require conf/machine/include/zgemma-essential.inc

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 += " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000"

# Gstreamer dvbmediasink
DVBMEDIASINK_CONFIG = "--with-h265 --with-vb8 --with-wma --with-wmv --with-pcm  --with-eac3 --with-amr --with-spark"

MACHINE_EXTRA_RRECOMMENDS += "\
	ffmpeg \
"

MACHINE_FEATURES += " alsa usbhost switchoff osdposition hdmicec no-opengl hisil hisil-3716mv430 ci ciplus-helper"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	${@bb.utils.contains("MACHINE_FEATURES", "hisil-${HICHIPSET}", "zgemma-libs-${HICHIPSET} zgemma-param-${HICHIPSET} zgemma-bootargs-${HICHIPSET} zgemma-bootlogo-${HICHIPSET} zgemma-fastboot-${HICHIPSET}" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "ciplus-helper", "ciplus-helper-${HICHIPSET}" , "", d)} \
	"

IMAGEDIR ?= "zgemma"
IMAGEDIRRECOVERY ?= "zgemma-recovery"
IMGDEPLOYDIR ?= "${DEPLOY_DIR_IMAGE}"

IMAGE_CMD_ubi_append = " \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}; \
	cp ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ubi ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/rootfs.ubi; \
	cp ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/uImage; \
	cp ${IMGDEPLOYDIR}/bootoptions.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/bootoptions.img; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/update_bootargs_${MACHINE}.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/update_bootargs_${MACHINE}.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/fastboot.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/bootargs.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/pq_param.bin; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/baseparam.img; \
	cp ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIR}/${MACHINE}/logo.img; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/${IMAGEDIR}/imageversion; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIR}; \
	zip -r ../${IMAGE_NAME}_usb.zip *; \
	cd ..; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
	rm -Rf ${IMAGEDIR}; \
	"
