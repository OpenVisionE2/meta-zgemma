DISTRO_FEATURES_append = " opengl"

IMAGEDIR = "${MACHINE}"

KERNELVERSION = "4.4.35"

# We know about rtc
MACHINE_FEATURES_BACKFILL_CONSIDERED += "rtc"

TARGET_ARCH = "arm"
DEFAULTTUNE = "cortexa15hf-neon-vfpv4"

SOC_FAMILY = "hisi3798mv200"
HICHIPSET = "3798mv200"
CHIPSET = "Hi3798Mv200"

STB_PLATFORM = "zgemmahisi3798mv200"

CMDLINE ?= "console=ttyAMA0,115200n8"

#Provider
PREFERRED_PROVIDER_virtual/kernel = "linux-zgemma"
PREFERRED_VERSION_linux-zgemma = "${KERNELVERSION}"
PREFERRED_PROVIDER_virtual/egl ?= "zgemma-mali-${HICHIPSET}"
PREFERRED_PROVIDER_virtual/libgles1 ?= "zgemma-mali-${HICHIPSET}"
PREFERRED_PROVIDER_virtual/libgles2 ?= "zgemma-mali-${HICHIPSET}"
PREFERRED_PROVIDER_virtual/libgbm ?= "zgemma-mali-${HICHIPSET}"
PREFERRED_PROVIDER_virtual/libgl ?= "mesa"
PREFERRED_PROVIDER_virtual/mesa ?= "mesa"
PREFERRED_PROVIDER_virtual/blindscan-dvbc = "zgemma-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/blindscan-dvbs = "zgemma-dvb-modules-${MACHINE}"
PREFERRED_PROVIDER_virtual/gstreamer1.0-dvbmediasink = "gstreamer1.0-plugin-dvbmediasink"
PREFERRED_PROVIDER_virtual/enigma2-mediaservice = "enigma2-plugin-systemplugins-servicehisilicon"

require conf/machine/include/tune-cortexa15.inc
require conf/machine/include/zgemma-essential.inc

# Gstreamer DVB mediasink
DVBMEDIASINK_CONFIG = "--with-wma --with-wmv --with-pcm --with-dts --with-eac3 --with-h265 --with-vb6 --with-vb8 --with-vb9 --with-spark"

# E2 OSD settings
EXTRA_OECONF_append_pn-enigma2 = " --with-alphablendingacceleration=always --with-blitaccelerationthreshold=250 --with-fillaccelerationthreshold=190000"

MACHINE_FEATURES += "alsa usbhost switchoff osdposition hdmicec hisil hisil-3798mv200 mali multitranscoding dvb-c wol emmc blindscan-tbs HDMI"

MACHINE_ESSENTIAL_EXTRA_RDEPENDS += "\
	${@bb.utils.contains("MACHINE_FEATURES", "hisil-${HICHIPSET}", "kernel-module-mali-${HICHIPSET} zgemma-mali-${HICHIPSET} zgemma-libs-${HICHIPSET} zgemma-param-${HICHIPSET} zgemma-bootargs-${HICHIPSET} zgemma-bootlogo-${HICHIPSET} zgemma-fastboot-${HICHIPSET}" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "hisil-recovery", "zgemma-recovery-${HICHIPSET}" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "wol", "zgemma-ethwol" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "ciplus-helper", "ciplus-helper-${HICHIPSET}" , "", d)} \
	${@bb.utils.contains("MACHINE_FEATURES", "SDcard", "zgemma-bootargs-extra-${MACHINE}" , "", d)} \
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
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/zgemma/fastboot.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/update_bootargs_${MACHINE}.bin ${IMGDEPLOYDIR}/zgemma/bootargs.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/fastboot.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/bootargs.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/pq_param.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/baseparam.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/logo.img; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/zgemma/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${IMGDEPLOYDIR}/zgemma/donate.txt; \
	echo "rename this file to 'force' to force an update without confirmation" > ${IMGDEPLOYDIR}/zgemma/noforce; \
	rm -f ${IMGDEPLOYDIR}/*.zip; \
	cd ${IMGDEPLOYDIR}/zgemma; \
	zip -r ../${IMAGE_NAME}_usb.zip *; \
	cd ..; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubi; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.ubifs; \
	rm -Rf zgemma; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}; \
	"

IMAGE_CMD_zgemmafastboot8gb_append = " \
	mkdir -p ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}; \
	mkdir -p ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/${KERNEL_FILE}; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.tar ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/rootfs.tar; \
	bzip2 ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/rootfs.tar; \
	echo "${IMAGE_NAME}" > ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > ${IMGDEPLOYDIR}/zgemma/${IMAGEDIR}/donate.txt; \
	echo "${IMAGE_NAME}_usb.zip" > ${IMGDEPLOYDIR}/zgemma/unforce_${MACHINE}.txt; \
	echo "Rename unforce_${MACHINE}.txt to force_${MACHINE}.txt and move it to the root of your usb-stick" > ${IMGDEPLOYDIR}/zgemma/force_${MACHINE}_READ.ME; \
	echo "When enter the recovery menu you're forcing that the image ${IMAGE_NAME}_usb.zip will been installed into linux-slot1" >> ${IMGDEPLOYDIR}/zgemma/force_${MACHINE}_READ.ME; \
	cp -f ${IMGDEPLOYDIR}/bootoptions.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/bootoptions.img; \
	cp -f ${IMGDEPLOYDIR}/misc-boot.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/misc-boot.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/fastboot.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/bootargs.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/fastboot.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/fastboot.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/bootargs.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/bootargs.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/pq_param.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/pqparam.bin; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/baseparam.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/baseparam.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/logo.img ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/logo.img; \
	cp -f ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}/${MACHINE}/recovery.bin ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/recovery.bin; \
	echo "${MACHINE}-${DATE}-RECOVERY" > ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/recoveryversion; \
	echo "***** ATTENTION *****" >${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "This RECOVERY only need when you have issue access the MULTIBOOT MENU" >>${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "The ${IMAGE_NAME}_recovery_usb.zip should been install normally once (or if there is an update.)" >>${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "This is needed for avoid images conflicts as the partition layout (bootargs) is of huge essential." >>${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	echo "A small change can destroy all your install images. So we can better leave it and not install it if it's not need." >>${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/recovery_${MACHINE}_READ.ME; \
	rm -f ${IMGDEPLOYDIR}/*.zip; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}; \
	echo "${IMAGE_NAME}" > imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > donate.txt; \
	zip -r ../${IMAGE_NAME}_recovery_emmc.zip *; \
	cd ..; \
	cp -f ${IMGDEPLOYDIR}/${IMAGE_NAME}${IMAGE_NAME_SUFFIX}.userdata.ext4 ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/userdata.ext4; \
	cp -f ${DEPLOY_DIR_IMAGE}/uImage ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}/${MACHINE}/uImage; \
	cd ${IMGDEPLOYDIR}/${IMAGEDIRRECOVERY}; \
	echo "${IMAGE_NAME}" > imageversion; \
	echo "https://forum.openvision.tech/app.php/donate" > donate.txt; \
	zip -r ../${IMAGE_NAME}_full_recovery_emmc.zip *; \
	cd ..; \
	rm -Rf ${IMAGEDIRRECOVERY}; \
	cd ${IMGDEPLOYDIR}/zgemma; \
	zip -r ../${IMAGE_NAME}_usb.zip *; \
	cd ..; \
	rm -f ${DEPLOY_DIR_IMAGE}/*.tar.bz2; \
	rm -Rf zgemma; \
	rm -Rf ${DEPLOY_DIR_IMAGE}/zgemma-partitions-${MACHINE}; \
	"

IMAGE_CMD_prepend = "\
	rm -Rf ${IMAGE_ROOTFS}/tmp/*; \
	"

EXTRA_ALSA = "mv200"
