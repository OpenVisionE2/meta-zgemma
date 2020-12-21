IMAGEDIR = "${MACHINETYPE}"

KERNELVERSION = "4.4.35"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa7hf"

SOC_FAMILY = "hisi3716mv430"
HICHIPSET = "3716mv430"
CHIPSET = "Hi3716Mv430"

STB_PLATFORM = "zgemmahisi3716mv430"

IMAGE_CLASSES += "zgemma-ubi_image"
IMAGE_FSTYPES += "ubi zgemmaubi"

MKUBIFS_ARGS = "-m 4096 -e 253952 -c 2048"
UBINIZE_ARGS = "-m 4096 -p 256KiB -s 4096"

CMDLINE ?= "console=ttyAMA0,115200n8"

MTD_KERNEL = "mtd9"
MTD_ROOTFS = "mtd10"
KERNEL_FILE = "uImage"
ROOTFS_FILE = "rootfs.ubi"

RCTYPE = "25"

#Provider
PREFERRED_PROVIDER_virtual/kernel = "linux-zgemma"
PREFERRED_VERSION_linux-zgemma = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink = "gstreamer1.0-plugin-dvbmediasink"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

require conf/machine/include/tune-cortexa7.inc
require conf/machine/include/zgemma-essential.inc

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 = " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000"

# Gstreamer dvbmediasink
DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 --with-h265 --with-vb6 --with-vb8 -with-spark"

MACHINE_FEATURES += "alsa usbhost switchoff osdposition hdmicec no-opengl hisil hisil-3716mv430 blindscan-tbs HDMI wol"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	${@bb.utils.contains("MACHINE_FEATURES", "hisil-${HICHIPSET}", "zgemma-libs-${HICHIPSET} zgemma-param-${HICHIPSET} zgemma-bootargs-${HICHIPSET} zgemma-bootlogo-${HICHIPSET} zgemma-fastboot-${HICHIPSET}" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "wol", "zgemma-ethwol" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "ciplus-helper", "ciplus-helper-${HICHIPSET}" , "", d)} \
	firmware-rtl8192eu \
	kernel-module-extrawlan-rtl8192eu \
	firmware-mt7601u \
	kernel-module-mt7601u \
	kernel-module-extrawlan-rtl8192fu \
	"

IMAGE_CMD_ubifs_prepend = " \
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

IMAGE_CMD_ubi_append = " \
	mkdir -p ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.ubi ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/${ROOTFS_FILE}; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/${KERNEL_FILE}; \
	cp -f ${IMGDEPLOYDIR}/bootoptions.img ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/bootoptions.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/update_bootargs_${MACHINE}.bin ${IMGDEPLOYDIR}/zgemma/update_bootargs_${MACHINE}.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/fastboot.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/bootargs.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/pq_param.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/baseparam.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/logo.img; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/zgemma/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${IMGDEPLOYDIR}/zgemma/donate.txt; \
	cd ${IMGDEPLOYDIR}/zgemma; \
	zip -r ../${IMAGE_NAME}_usb.zip *; \
	cd ..; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
	rm -Rf zgemma; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}; \
	"
