SRCDATE = "20200916"

require zgemma-bootlogo.inc

SRC_URI[md5sum] = "a4be4429300800b3901c85ef8af95037"
SRC_URI[sha256sum] = "56acac6f3f23a7769a6f489658d14e78c7803b707fb6712b15c02cd7f1399671"

COMPATIBLE_MACHINE = "^(h9|h9combo|h10|i55plus|h9combose|h9se|i55plusse)$"

SRC_URI = "http://www.zgemma.org/downloads/zgemma-bootlogo-${HICHIPSET}-${SRCDATE}.zip"
