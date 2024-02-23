#ifndef DRV_EEPROM_H
#define DRV_EEPROM_H

#define EEPROM_I2C_ADDRESS	0x52
#define EEPROM_SIZE		512
#define EEPROM_PAGE_SIZE	256
#define EEPROM_MAX_WRITE_SIZE	16

#define CTL_CODE(function, method) ((4 << 16) | ((function) << 2) | (method))

#define METHOD_BUFFERED		0
#define METHOD_NEITHER		3

#define SOMINFO_READ_EEPROM	CTL_CODE(2100, METHOD_BUFFERED)
#define SOMINFO_WRITE_EEPROM	CTL_CODE(2101, METHOD_BUFFERED)

#define VAR_EEPROM_MAGIC       0x384D /* == HEX("8M") */

/* Number of DRAM adjustment tables */
#define DRAM_TABLE_NUM 7

struct __attribute__((packed)) var_eeprom
{
	uint16_t magic;                /* 00-0x00 - magic number       */
	uint8_t partnum[3];            /* 02-0x02 - part number        */
	uint8_t assembly[10];          /* 05-0x05 - assembly number    */
	uint8_t date[9];               /* 15-0x0f - build date         */
	uint8_t mac[6];                /* 24-0x18 - MAC address        */
	uint8_t somrev;                /* 30-0x1e - SOM revision       */
	uint8_t version;               /* 31-0x1f - EEPROM version     */
	uint8_t features;              /* 32-0x20 - SOM features       */
	uint8_t dramsize;              /* 33-0x21 - DRAM size          */
	uint8_t off[DRAM_TABLE_NUM+1]; /* 34-0x22 - DRAM table offsets */
	uint8_t partnum2[5];           /* 42-0x2a - part number        */
	uint8_t reserved[3];           /* 47 0x2f - reserved           */
};

static inline int var_eeprom_is_valid(struct var_eeprom *e)
{
	if (__builtin_bswap16(e->magic) != VAR_EEPROM_MAGIC) {
		board_print(3, "Invalid EEPROM magic 0x%hx, expected 0x%hx\n",
			__builtin_bswap16(e->magic), VAR_EEPROM_MAGIC);
		return 0;
	}

	return 1;
}

extern void eeprom_i2c_init(void);
extern status_t eeprom_i2c_write(uint8_t device_addr, uint8_t reg, void *data, uint32_t dataLength);
extern status_t eeprom_i2c_read(uint8_t device_addr, uint8_t reg, void *data, uint32_t dataLength);

#endif
