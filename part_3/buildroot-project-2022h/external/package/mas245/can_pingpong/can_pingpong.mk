################################################################################
#
# can_pingpong 
#
################################################################################

CAN_PINGPONG_VERSION = 3.14
#HELLOWORLD_VERSION = merk kryptosjekksum er å foretrekke...
CAN_PINGPONG_SITE = $(TOPDIR)/../mas245/can_pingpong
CAN_PINGPONG_SITE_METHOD = local
CAN_PINGPONG_DEPENDENCIES = qt5base
#HELLOWORLD_LICENSE = MIT
#HELLOWORLD_LICENSE_FILES = README.md


#define CAN_PINGPONG_BUILD_CMDS
#	(cd $(@D); $(TARGET_MAKE_ENV) $(QT_MAKE))
#endef

define CAN_PINGPONG_CONFIGURE_CMDS
	(cd $(@D); \
		$(TARGET_MAKE_ENV) \
		$(HOST_DIR)/usr/bin/qmake \
			./can_pingpong.pro \
	)
endef

define CAN_PINGPONG_BUILD_CMDS
	$(TARGET_MAKE_ENV) $(MAKE) -C $(@D)
endef

define CAN_PINGPONG_INSTALL_TARGET_CMDS
	$(INSTALL) -D -m 0755 $(@D)/can_pingpong $(TARGET_DIR)/usr/bin 
endef

$(eval $(generic-package))


