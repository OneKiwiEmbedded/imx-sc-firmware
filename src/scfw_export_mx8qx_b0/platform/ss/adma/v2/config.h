/*
** ###################################################################
**
**     Copyright (c) 2016 Freescale Semiconductor, Inc.
**     Copyright 2017-2022 NXP
**
**     Redistribution and use in source and binary forms, with or without modification,
**     are permitted provided that the following conditions are met:
**
**     o Redistributions of source code must retain the above copyright notice, this list
**       of conditions and the following disclaimer.
**
**     o Redistributions in binary form must reproduce the above copyright notice, this
**       list of conditions and the following disclaimer in the documentation and/or
**       other materials provided with the distribution.
**
**     o Neither the name of the copyright holder nor the names of its
**       contributors may be used to endorse or promote products derived from this
**       software without specific prior written permission.
**
**     THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
**     ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
**     WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
**     DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
**     ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
**     (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
**     LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
**     ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
**     (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
**     SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
**
**
** ###################################################################
*/

/*==========================================================================*/
/*!
 * @file
 *
 * Header file containing the entry points and debug resource strings
 * for the ADMA subsystem.
 *
 * @addtogroup ADMA_SS
 * @{
 */
/*==========================================================================*/

/* DO NOT EDIT - This file auto generated by bin/perl/config_ss_h.pl */

#ifndef SC_SS_ADMA_CONFIG_H
#define SC_SS_ADMA_CONFIG_H

/*!
 * This define defines the number of resources.
 */
#define SS_NUM_RSRC_ADMA 148U

/*! Define used to create subsystem function prototypes */
#define SS_FUNC_PROTO_ADMA \
    void ss_trans_power_mode_adma(sc_sub_t ss, ss_idx_t ss_idx, ss_ridx_t \
        rsrc_idx, sc_pm_power_mode_t from_mode, sc_pm_power_mode_t \
        to_mode); \
    sc_err_t ss_set_clock_parent_adma(sc_sub_t ss, ss_idx_t ss_idx, \
        ss_ridx_t rsrc_idx, sc_pm_clk_t clk, sc_pm_clk_parent_t \
        new_parent); \
    sc_err_t ss_cpu_start_adma(sc_sub_t ss, ss_idx_t ss_idx, ss_ridx_t \
        rsrc_idx, sc_bool_t enable, sc_faddr_t addr); \
    sc_err_t ss_set_control_adma(sc_sub_t ss, ss_idx_t ss_idx, ss_ridx_t \
        rsrc_idx, uint32_t ctrl, uint32_t val); \
    void ss_do_mem_repair_adma(sc_sub_t ss, dsc_pdom_t pd, sc_bool_t \
        enable); \
    void ss_updown_adma(sc_sub_t ss, sc_bool_t up); \
    void ss_prepost_power_mode_adma(sc_sub_t ss, dsc_pdom_t pd, \
        ss_prepost_t type, sc_pm_power_mode_t from_mode, sc_pm_power_mode_t \
        to_mode, sc_bool_t rom_boot); \
    void ss_link_enable_adma(sc_sub_t ss, dsc_pdom_t pd, sc_bool_t enable); \
    void ss_adb_enable_adma(sc_sub_t ss, sc_sub_t remote, sc_bool_t \
        enable); \
    void ss_adb_wait_adma(sc_sub_t ss, sc_sub_t remote, sc_bool_t enable); \


/*!
 * This define is used to override the default SS function entry points.
 * If this isn't defined, then the SS uses functions in base.
 */
#define SS_EP_INIT_ADMA \
    { \
        ss_init_base, \
        ss_trans_power_mode_adma, \
        ss_rsrc_reset_base, \
        ss_set_cpu_power_mode_base, \
        ss_set_cpu_resume_base, \
        ss_req_sys_if_power_mode_base, \
        ss_set_clock_rate_base, \
        ss_get_clock_rate_base, \
        ss_clock_enable_base, \
        ss_force_clock_enable_base, \
        ss_set_clock_parent_adma, \
        ss_get_clock_parent_base, \
        ss_is_rsrc_accessible_base, \
        ss_mu_irq_base, \
        ss_cpu_start_adma, \
        ss_rdc_enable_base, \
        ss_rdc_set_master_base, \
        ss_rdc_set_peripheral_base, \
        ss_rdc_set_memory_base, \
        ss_set_control_adma, \
        ss_get_control_base, \
        ss_irq_enable_base, \
        ss_irq_status_base, \
        ss_irq_trigger_base, \
        ss_dump_base, \
        ss_do_mem_repair_adma, \
        ss_updown_adma, \
        ss_prepost_power_mode_adma, \
        ss_iso_disable_base, \
        ss_link_enable_adma, \
        ss_ssi_power_base, \
        ss_ssi_bhole_mode_base, \
        ss_ssi_pause_mode_base, \
        ss_ssi_wait_idle_base, \
        ss_adb_enable_adma, \
        ss_adb_wait_adma, \
        ss_prepost_clock_mode_base, \
        ss_rdc_is_did_vld_base, \
    }

#ifdef DEBUG
    /*!
     * This define is used to name resources for debug output.
     */
    #define RNAME_INIT_ADMA_0 \
        "LCD_0", \
        "ASRC_0", \
        "ESAI_0", \
        "SPDIF_0", \
        "SAI_0", \
        "SAI_1", \
        "SAI_2", \
        "SAI_3", \
        "GPT_5", \
        "GPT_6", \
        "GPT_7", \
        "GPT_8", \
        "GPT_9", \
        "GPT_10", \
        "DMA_0_CH0", \
        "DMA_0_CH1", \
        "DMA_0_CH2", \
        "DMA_0_CH3", \
        "DMA_0_CH4", \
        "DMA_0_CH5", \
        "DMA_0_CH6", \
        "DMA_0_CH7", \
        "DMA_0_CH8", \
        "DMA_0_CH9", \
        "DMA_0_CH10", \
        "DMA_0_CH11", \
        "DMA_0_CH12", \
        "DMA_0_CH13", \
        "DMA_0_CH14", \
        "DMA_0_CH15", \
        "DMA_0_CH16", \
        "DMA_0_CH17", \
        "DMA_0_CH18", \
        "DMA_0_CH19", \
        "DMA_0_CH20", \
        "DMA_0_CH21", \
        "DMA_0_CH22", \
        "DMA_0_CH23", \
        "DMA_0_CH24", \
        "DMA_0_CH25", \
        "DMA_0_CH26", \
        "DMA_0_CH27", \
        "DMA_0_CH28", \
        "DMA_0_CH29", \
        "DMA_0_CH30", \
        "DMA_0_CH31", \
        "ASRC_1", \
        "SAI_4", \
        "SAI_5", \
        "AMIX", \
        "MQS_0", \
        "DMA_1_CH0", \
        "DMA_1_CH1", \
        "DMA_1_CH2", \
        "DMA_1_CH3", \
        "DMA_1_CH4", \
        "DMA_1_CH5", \
        "DMA_1_CH6", \
        "DMA_1_CH7", \
        "DMA_1_CH8", \
        "DMA_1_CH9", \
        "DMA_1_CH10", \
        "DMA_1_CH11", \
        "DMA_1_CH12", \
        "DMA_1_CH13", \
        "DMA_1_CH14", \
        "DMA_1_CH15", \
        "SPI_0", \
        "SPI_1", \
        "SPI_2", \
        "SPI_3", \
        "UART_0", \
        "UART_1", \
        "UART_2", \
        "UART_3", \
        "DMA_2_CH0", \
        "DMA_2_CH1", \
        "DMA_2_CH2", \
        "DMA_2_CH3", \
        "DMA_2_CH4", \
        "DMA_2_CH5", \
        "DMA_2_CH6", \
        "DMA_2_CH7", \
        "DMA_2_CH8", \
        "DMA_2_CH9", \
        "DMA_2_CH10", \
        "DMA_2_CH11", \
        "DMA_2_CH12", \
        "DMA_2_CH13", \
        "DMA_2_CH14", \
        "DMA_2_CH15", \
        "DMA_2_CH16", \
        "DMA_2_CH17", \
        "DMA_2_CH18", \
        "DMA_2_CH19", \
        "DMA_2_CH20", \
        "DMA_2_CH21", \
        "DMA_2_CH22", \
        "DMA_2_CH23", \
        "DMA_2_CH24", \
        "DMA_2_CH25", \
        "DMA_2_CH26", \
        "DMA_2_CH27", \
        "DMA_2_CH28", \
        "DMA_2_CH29", \
        "DMA_2_CH30", \
        "DMA_2_CH31", \
        "I2C_0", \
        "I2C_1", \
        "I2C_2", \
        "I2C_3", \
        "ADC_0", \
        "FTM_0", \
        "FTM_1", \
        "CAN_0", \
        "CAN_1", \
        "CAN_2", \
        "DMA_3_CH0", \
        "DMA_3_CH1", \
        "DMA_3_CH2", \
        "DMA_3_CH3", \
        "DMA_3_CH4", \
        "DMA_3_CH5", \
        "DMA_3_CH6", \
        "DMA_3_CH7", \
        "DMA_3_CH8", \
        "DMA_3_CH9", \
        "DMA_3_CH10", \
        "DMA_3_CH11", \
        "DMA_3_CH12", \
        "DMA_3_CH13", \
        "DMA_3_CH14", \
        "DMA_3_CH15", \
        "IRQSTR_M4_0", \
        "IRQSTR_M4_1", \
        "GIC", \
        "DSP", \
        "DSP_RAM", \
        "LCD_0_PWM_0", \
        "AUDIO_PLL_0", \
        "AUDIO_PLL_1", \
        "AUDIO_CLK_0", \
        "AUDIO_CLK_1", \
        "MCLK_OUT_0", \
        "MCLK_OUT_1", \
        "IRQSTR_SCU2", \
        "IRQSTR_DSP", \
        "ELCDIF_PLL", \

#endif

#endif /* SC_SS_ADMA_CONFIG_H */

/** @} */

