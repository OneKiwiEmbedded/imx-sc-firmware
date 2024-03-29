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
 * for the CONN subsystem.
 *
 * @addtogroup CONN_SS
 * @{
 */
/*==========================================================================*/

/* DO NOT EDIT - This file auto generated by bin/perl/config_ss_h.pl */

#ifndef SC_SS_CONN_CONFIG_H
#define SC_SS_CONN_CONFIG_H

/*!
 * This define defines the number of resources.
 */
#define SS_NUM_RSRC_CONN 16U

/*! Define used to create subsystem function prototypes */
#define SS_FUNC_PROTO_CONN \
    void ss_init_conn(sc_sub_t ss, sc_bool_t api_phase); \
    sc_err_t ss_set_clock_parent_conn(sc_sub_t ss, ss_idx_t ss_idx, \
        ss_ridx_t rsrc_idx, sc_pm_clk_t clk, sc_pm_clk_parent_t \
        new_parent); \
    sc_err_t ss_set_control_conn(sc_sub_t ss, ss_idx_t ss_idx, ss_ridx_t \
        rsrc_idx, uint32_t ctrl, uint32_t val); \
    void ss_updown_conn(sc_sub_t ss, sc_bool_t up); \
    void ss_prepost_power_mode_conn(sc_sub_t ss, dsc_pdom_t pd, \
        ss_prepost_t type, sc_pm_power_mode_t from_mode, sc_pm_power_mode_t \
        to_mode, sc_bool_t rom_boot); \
    void ss_iso_disable_conn(sc_sub_t ss, dsc_pdom_t pd, sc_bool_t enable); \


/*!
 * This define is used to override the default SS function entry points.
 * If this isn't defined, then the SS uses functions in base.
 */
#define SS_EP_INIT_CONN \
    { \
        ss_init_conn, \
        ss_trans_power_mode_base, \
        ss_rsrc_reset_base, \
        ss_set_cpu_power_mode_base, \
        ss_set_cpu_resume_base, \
        ss_req_sys_if_power_mode_base, \
        ss_set_clock_rate_base, \
        ss_get_clock_rate_base, \
        ss_clock_enable_base, \
        ss_force_clock_enable_base, \
        ss_set_clock_parent_conn, \
        ss_get_clock_parent_base, \
        ss_is_rsrc_accessible_base, \
        ss_mu_irq_base, \
        ss_cpu_start_base, \
        ss_rdc_enable_base, \
        ss_rdc_set_master_base, \
        ss_rdc_set_peripheral_base, \
        ss_rdc_set_memory_base, \
        ss_set_control_conn, \
        ss_get_control_base, \
        ss_irq_enable_base, \
        ss_irq_status_base, \
        ss_irq_trigger_base, \
        ss_dump_base, \
        ss_do_mem_repair_base, \
        ss_updown_conn, \
        ss_prepost_power_mode_conn, \
        ss_iso_disable_conn, \
        ss_link_enable_base, \
        ss_ssi_power_base, \
        ss_ssi_bhole_mode_base, \
        ss_ssi_pause_mode_base, \
        ss_ssi_wait_idle_base, \
        ss_adb_enable_base, \
        ss_adb_wait_base, \
        ss_prepost_clock_mode_base, \
        ss_rdc_is_did_vld_base, \
    }

#ifdef DEBUG
    /*!
     * This define is used to name resources for debug output.
     */
    #define RNAME_INIT_CONN_0 \
        "SDHC_0", \
        "SDHC_1", \
        "SDHC_2", \
        "ENET_0", \
        "ENET_1", \
        "DMA_4_CH0", \
        "DMA_4_CH1", \
        "DMA_4_CH2", \
        "DMA_4_CH3", \
        "DMA_4_CH4", \
        "USB_0", \
        "USB_1", \
        "USB_0_PHY", \
        "USB_2", \
        "USB_2_PHY", \
        "NAND", \

#endif

#endif /* SC_SS_CONN_CONFIG_H */

/** @} */

