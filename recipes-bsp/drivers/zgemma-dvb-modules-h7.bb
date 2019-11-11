KV = "4.10.12"
SRCDATE = "20191110"

PROVIDES = "virtual/blindscan-dvbs"

require zgemma-dvb-modules.inc

SRC_URI[arm.md5sum] = "7001d501226ca2bf920759ba432c1192"
SRC_URI[arm.sha256sum] = "21fc4f4066852b8b42a13333d7dc718451520ad84b9d24ccd9dc8ca589bf5059"

COMPATIBLE_MACHINE = "^(h7)$"
