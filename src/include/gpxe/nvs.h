#ifndef _GPXE_NVS_H
#define _GPXE_NVS_H

/** @file
 *
 * Non-volatile storage
 *
 */

#include <stdint.h>

/** A non-volatile storage device */
struct nvs_device {
	/** Word length, in bits */
	unsigned int word_len;
	/** Device size (in words) */
	unsigned int size;
	/** Data block size (in words)
	 *
	 * This is the block size used by the device.  It must be a
	 * power of two.  Data reads and writes must not cross a block
	 * boundary.
	 *
	 * Many devices allow reads to cross a block boundary, and
	 * restrict only writes.  For the sake of simplicity, we
	 * assume that the same restriction applies to both reads and
	 * writes.
	 */
	unsigned int block_size;
	/** Read data from device
	 *
	 * @v nvs		NVS device
	 * @v address		Address from which to read
	 * @v data		Data buffer
	 * @v len		Length of data buffer
	 * @ret rc		Return status code
	 *
	 * Reads may not cross a block boundary.
	 */
	int ( * read ) ( struct nvs_device *nvs, unsigned int address,
			 void *data, size_t len );
	/** Write data to device
	 *
	 * @v nvs		NVS device
	 * @v address		Address to which to write
	 * @v data		Data buffer
	 * @v len		Length of data buffer
	 * @ret rc		Return status code
	 *
	 * Writes may not cross a block boundary.
	 */
	int ( * write ) ( struct nvs_device *nvs, unsigned int address,
			  const void *data, size_t len );
};

extern int nvs_read ( struct nvs_device *nvs, unsigned int address,
		      void *data, size_t len );
extern int nvs_write ( struct nvs_device *nvs, unsigned int address,
		       const void *data, size_t len );

#endif /* _GPXE_NVS_H */
