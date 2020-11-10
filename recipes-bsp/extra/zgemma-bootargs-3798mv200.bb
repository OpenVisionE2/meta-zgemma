SRCDATE = "20200916"

require zgemma-bootargs.inc

SRC_URI[md5sum] = "378622e172cb6c70d50c988badf30a04"
SRC_URI[sha256sum] = "cfe68f0a7248af35f42ea74f13b2fdbbec7b9682940f9725da914c44f5a05f5f"

COMPATIBLE_MACHINE = "^(h9|h9combo|h10|i55plus|h9combose|h9se|i55plusse)$"

SRC_URI = "http://www.zgemma.org/downloads/zgemma-bootargs-${HICHIPSET}-${SRCDATE}.zip"
