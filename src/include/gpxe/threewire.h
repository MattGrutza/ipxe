#ifndef _GPXE_THREEWIRE_H
#define _GPXE_THREEWIRE_H

/** @file
 *
 * Three-wire serial interface
 *
 * The Atmel three-wire interface is a subset of the (newer) SPI
 * interface, and is implemented here as a layer on top of the SPI
 * support.
 */

#include <gpxe/spi.h>

/**
 * @defgroup tcmds Three-wire commands
 * @{
 */

/** Read data from memory array */
#define THREEWIRE_READ 0x6

/** @} */

extern int threewire_read ( struct nvs_device *nvs, unsigned int address,
			    void *data, size_t len );

/**
 * @defgroup tdevs Three-wire device types
 * @{
 */

static inline __attribute__ (( always_inline )) void
init_at93cx6 ( struct spi_device *device, unsigned int organisation ) {
	device->nvs.word_len = organisation;
	device->nvs.block_size = 1;
	device->command_len = 3,
	device->nvs.read = threewire_read;
}

/**
 * Initialise Atmel AT93C46 serial EEPROM
 *
 * @v device		SPI device
 * @v organisation	Word organisation (8 or 16)
 */
static inline __attribute__ (( always_inline )) void
init_at93c46 ( struct spi_device *device, unsigned int organisation ) {
	device->nvs.size = ( 1024 / organisation );
	device->address_len = ( ( organisation == 8 ) ? 7 : 6 );
	init_at93cx6 ( device, organisation );
}

/**
 * Initialise Atmel AT93C56 serial EEPROM
 *
 * @v device		SPI device
 * @v organisation	Word organisation (8 or 16)
 */
static inline __attribute__ (( always_inline )) void
init_at93c56 ( struct spi_device *device, unsigned int organisation ) {
	device->nvs.size = ( 2048 / organisation );
	device->address_len = ( ( organisation == 8 ) ? 9 : 8 );
	init_at93cx6 ( device, organisation );
}

/** @} */

#endif /* _GPXE_THREEWIRE_H */
