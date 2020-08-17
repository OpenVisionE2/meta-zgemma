SRCDATE = "20200818"

require zgemma-fastboot.inc

SRC_URI[md5sum] = "02f51b007db30894848dc82e77d8233e"
SRC_URI[sha256sum] = "b4ba9cf3acc1c388a2e871bee454f98c9ccf056ac45b5f0bb7919ea91839d394"

COMPATIBLE_MACHINE = "^(h0|h8)$"

SRC_URI = "http://source.mynonpublic.com/zgemma/zgemma-fastboot-${HICHIPSET}-${SRCDATE}.zip"
