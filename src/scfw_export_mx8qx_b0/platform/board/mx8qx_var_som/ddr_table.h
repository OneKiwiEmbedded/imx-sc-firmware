#ifndef __MX8QX_VAR_SOM_DDR_TABLE_H__
#define __MX8QX_VAR_SOM_DDR_TABLE_H__

enum dcd_cmd {
	DCD_WRITE,
	DCD_SET_BIT,
	DCD_CLR_BIT,
	DCD_CHECK_BITS_SET,
	DCD_CHECK_BITS_CLR,
	DCD_CHECK_ANY_BIT_SET,
	DCD_CHECK_ANY_BIT_CLR,
	DCD_RUN_CBT,
	DCD_RDBI_BIT_DESKEW,
	DCD_LPDDR4_DERATE_INIT,
	DCD_VREF_TRAIN_SW,
};

struct __attribute__((packed)) dram_cfg_param {
	uint8_t  cmd;
	uint32_t reg;
	uint32_t val;
};

extern struct dram_cfg_param dcd_table[];
extern int dcd_table_size;

#endif
