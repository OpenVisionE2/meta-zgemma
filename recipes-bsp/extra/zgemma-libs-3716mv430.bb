SRCDATE = "20200818"

require zgemma-libs.inc

SRC_URI[md5sum] = "6df244e225f184a593f89341c2669d9a"
SRC_URI[sha256sum] = "5a979d266087a3948b426e63a1f6868527a9fb909044a28deb3db64feba0148d"

COMPATIBLE_MACHINE = "^(h0|h8)$"

SRC_URI = "http://source.mynonpublic.com/zgemma/zgemma-libs-${HICHIPSET}-${SRCDATE}.zip"
