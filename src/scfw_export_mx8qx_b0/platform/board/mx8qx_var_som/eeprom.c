#include "main/scfw.h"
#include "main/main.h"
#include "fsl_device_registers.h"
#include "drivers/lpi2c/fsl_lpi2c.h"
#include "fsl_common.h"
#include "all_svc.h"

#include "pads.h"
#include "drivers/pad/fsl_pad.h"

/*--------------------------------------------------------------------------*/
/* Initialize EEPROM I2C bus                                                */
/*--------------------------------------------------------------------------*/
void eeprom_i2c_init(void)
{
            sc_pm_clock_rate_t rate = SC_24MHZ;
            static lpi2c_master_config_t lpi2c_masterConfig;

            /* Power up the I2C and configure clocks */
            pm_force_resource_power_mode_v(SC_R_SC_I2C,
                SC_PM_PW_MODE_ON);
            (void) pm_set_clock_rate(SC_PT, SC_R_SC_I2C,
                SC_PM_CLK_PER, &rate);
            (void) pm_force_clock_enable(SC_R_SC_I2C, SC_PM_CLK_PER,
                SC_TRUE);

            /* Initialize the pads used to communicate with the EEPROM */
            pad_force_mux(SC_P_PMIC_I2C_SDA, 0,
                SC_PAD_CONFIG_OD_IN, SC_PAD_ISO_OFF);
            (void) pad_set_gp_28fdsoi(SC_PT, SC_P_PMIC_I2C_SDA,
                SC_PAD_28FDSOI_DSE_18V_1MA, SC_PAD_28FDSOI_PS_PU);
            pad_force_mux(SC_P_PMIC_I2C_SCL, 0,
                SC_PAD_CONFIG_OD_IN, SC_PAD_ISO_OFF);
            (void) pad_set_gp_28fdsoi(SC_PT, SC_P_PMIC_I2C_SCL,
                SC_PAD_28FDSOI_DSE_18V_1MA, SC_PAD_28FDSOI_PS_PU);

            /* Initialize the I2C used to communicate with the PMIC */
            LPI2C_MasterGetDefaultConfig(&lpi2c_masterConfig);
            LPI2C_MasterInit(LPI2C_PMIC, &lpi2c_masterConfig, SC_24MHZ);

            /* Delay to allow I2C to settle */
            SystemTimeDelay(2U);
}

/*--------------------------------------------------------------------------*/
/* Write to the EEPROM via the I2C                                          */
/*--------------------------------------------------------------------------*/
static status_t eeprom_i2c_write_sub(uint8_t device_addr, uint8_t reg, void *data,
                              uint32_t dataLength)
{
    status_t status = I32(kStatus_Success);
    size_t rx, tx;

    do
    {
            status = LPI2C_MasterStart(LPI2C_SC, device_addr,
                kLPI2C_Write);
            if (status != I32(kStatus_Success))
            {
                break;
            }

            status = LPI2C_MasterSend(LPI2C_SC, &reg, 1);
            if (status != I32(kStatus_Success))
            {
                break;
            }

            status = LPI2C_MasterSend(LPI2C_SC, data, dataLength);
            if (status != I32(kStatus_Success))
            {
                break;
            }

            status = LPI2C_MasterStop(LPI2C_SC);
            if (status != I32(kStatus_Success))
            {
                break;
            }

            do/* FIFO empty barrier */
            {
                LPI2C_MasterGetFifoCounts(LPI2C_SC, &rx, &tx);
            }
            while(tx>0U);
            /* if we get this far we have succeeded */
    } while (SC_FALSE);

    return status;
}

/*--------------------------------------------------------------------------*/
/* Write to the EEPROM via the I2C (with clock management)                  */
/*--------------------------------------------------------------------------*/
status_t eeprom_i2c_write(uint8_t device_addr, uint8_t reg, void *data, uint32_t dataLength)
{
#ifdef SC_MANAGE_LPI2C_CLK
    /* Enable clocking using LPCG */
    CLOCK_EnableClockEx(kCLOCK_LPI2C_SC);

    /* Do the transfer */
    status_t stat = i2c_write_sub(device_addr, reg, data, dataLength);

    if(stat != I32(kStatus_Success))/* do a MasterStop if we ever fail */
    {
        error_print("I2C Error: %d \n", stat);
        (void) LPI2C_MasterStop(LPI2C_SC);
    }

    /* Enter exclusive attempt to disable clock */
    uint32_t lpcgVal = CLOCK_DisableClockExEnter(kCLOCK_LPI2C_SC);

    /* Check if conditions allow clock gating */
    if (!LPI2C_MasterGetBusIdleState(LPI2C_SC))
    {
        /* Mask to disable IPG and BAUD clocks */
        uint32_t lpcgMask = ~(BIT(LPCG__SS_SCU__IPG_CLK__SWEN) |
                             BIT(LPCG__SS_SCU__PER_CLK__SWEN));

        lpcgVal &= lpcgMask;
    }

    /* Leave exclusive attempt to disable clock */
    CLOCK_DisableClockExLeave(kCLOCK_LPI2C_SC, lpcgVal);

    return stat;
#else
    return eeprom_i2c_write_sub(device_addr, reg, data, dataLength);
#endif
}

/*--------------------------------------------------------------------------*/
/* Read from the EEPROM via I2C                                             */
/*--------------------------------------------------------------------------*/
static status_t eeprom_i2c_read_sub(uint8_t device_addr, uint8_t reg, void *data,
                             uint32_t dataLength)
{
    status_t status = I32(kStatus_Success);
    uint32_t flags;

    do
    {
        status = LPI2C_MasterStart(LPI2C_SC, device_addr, kLPI2C_Write);
        if (status != I32(kStatus_Success))
        {
            break;
        }

        status = LPI2C_MasterSend(LPI2C_SC, &reg, 1);
        if (status != I32(kStatus_Success) )
        {
            break;
        }

        status = LPI2C_MasterStart(LPI2C_SC, device_addr, kLPI2C_Read);
        if (status != I32(kStatus_Success))
        {
            break;
        }

        status = LPI2C_MasterReceive(LPI2C_SC, data, dataLength);
        if (status != I32(kStatus_Success))
        {
            break;
        }

        while (SC_TRUE)
        {
            flags = LPI2C_MasterGetStatusFlags(LPI2C_SC);

            if ((flags & U32(kLPI2C_MasterNackDetectFlag)) == 0U)
            {
                break;
            }

            if ((flags & i2c_error_flags) != 0U)
            {
                error_print("i2c error flag: %d \n", flags);
            }
        }
        status =  LPI2C_MasterStop(LPI2C_SC);
        /* if we got here we had a succesful read */
    } while (SC_FALSE);

    return status;
}

/*--------------------------------------------------------------------------*/
/* Read from the EEPROM via I2C (with clock management)                     */
/*--------------------------------------------------------------------------*/
status_t eeprom_i2c_read(uint8_t device_addr, uint8_t reg, void *data, uint32_t dataLength)
{
#ifdef SC_MANAGE_LPI2C_CLK
    /* Enable clocking using LPCG */
    CLOCK_EnableClockEx(kCLOCK_LPI2C_SC);

    /* Do the transfer */
    status_t stat = i2c_read_sub(device_addr, reg, data, dataLength);

    if(stat != I32(kStatus_Success))/* do a MasterStop if we ever fail */
    {
        error_print("I2C error : %d \n", stat);
        (void) LPI2C_MasterStop(LPI2C_SC);
    }

    /* Enter exclusive attempt to disable clock */
    uint32_t lpcgVal = CLOCK_DisableClockExEnter(kCLOCK_LPI2C_SC);

    /* Check if conditions allow clock gating */
    if (!LPI2C_MasterGetBusIdleState(LPI2C_SC))
    {
        /* Mask to disable IPG and BAUD clocks */
        uint32_t lpcgMask = ~(BIT(LPCG__SS_SCU__IPG_CLK__SWEN) |
                             BIT(LPCG__SS_SCU__PER_CLK__SWEN));

        lpcgVal &= lpcgMask;
    }

    /* Leave exclusive attempt to disable clock */
    CLOCK_DisableClockExLeave(kCLOCK_LPI2C_SC, lpcgVal);

    return stat;
#else
    return eeprom_i2c_read_sub(device_addr, reg, data, dataLength);
#endif
}
