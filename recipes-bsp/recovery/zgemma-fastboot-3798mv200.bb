SRCDATE = "20200916"

require zgemma-fastboot.inc

SRC_URI[md5sum] = "ec44347531c17802e9b0346121e6ea13"
SRC_URI[sha256sum] = "ba7caebea61a512f598ac60ceafa151252e73452e02aaf7a617282b4d2d8e7de"

COMPATIBLE_MACHINE = "^(h9|h9combo|h10|i55plus|h9combose|h9se|i55plusse)$"

SRC_URI = "http://www.zgemma.org/downloads/zgemma-fastboot-${HICHIPSET}-${SRCDATE}.zip"
