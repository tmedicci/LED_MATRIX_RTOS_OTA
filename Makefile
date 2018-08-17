# Main settings includes
include	../settings.mk

# Individual project settings (Optional)
#BOOT		= new
#APP		= 1
#SPI_SPEED	= 40
#SPI_MODE	= QIO
#SPI_SIZE_MAP	= 2
ESPPORT		= COM26
ESPBAUD		= 115200

# Basic project settings
MODULES	= driver user
LIBS	= c gcc hal phy pp net80211 lwip wpa main crypto

# Root includes
include	../common_nonos.mk
