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
 * for the A35 subsystem.
 *
 * @addtogroup A35_SS
 * @{
 */
/*==========================================================================*/

/* DO NOT EDIT - This file auto generated by bin/perl/config_ss_h.pl */

#ifndef SC_SS_A35_CONFIG_H
#define SC_SS_A35_CONFIG_H

/*!
 * This define defines the number of resources.
 */
#define SS_NUM_RSRC_A35 5U

/*! Define used to create subsystem function prototypes */
#define SS_FUNC_PROTO_A35 \
    void ss_init_a35(sc_sub_t ss, sc_bool_t api_phase); \
    sc_err_t ss_set_cpu_power_mode_a35(sc_sub_t ss, ss_idx_t ss_idx, \
        ss_ridx_t rsrc_idx, sc_pm_power_mode_t mode, sc_pm_wake_src_t \
        wake_src); \
    sc_err_t ss_set_cpu_resume_a35(sc_sub_t ss, ss_idx_t ss_idx, ss_ridx_t \
        rsrc_idx, sc_bool_t isPrimary, sc_faddr_t addr); \
    sc_err_t ss_req_sys_if_power_mode_a35(sc_sub_t ss, ss_idx_t ss_idx, \
        ss_ridx_t rsrc_idx, sc_pm_sys_if_t sys_if, sc_pm_power_mode_t hpm, \
        sc_pm_power_mode_t lpm); \
    sc_err_t ss_set_clock_rate_a35(sc_sub_t ss, ss_idx_t ss_idx, ss_ridx_t \
        rsrc_idx, sc_pm_clk_t clk, sc_pm_clock_rate_t *rate); \
    sc_err_t ss_cpu_start_a35(sc_sub_t ss, ss_idx_t ss_idx, ss_ridx_t \
        rsrc_idx, sc_bool_t enable, sc_faddr_t addr); \
    void ss_rdc_set_master_a35(sc_sub_t ss, ss_idx_t ss_idx, ss_ridx_t \
        rsrc_idx, sc_bool_t valid, sc_bool_t lock, sc_rm_spa_t sa, \
        sc_rm_spa_t pa, sc_rm_did_t did, sc_rm_sid_t sid, uint8_t cid); \
    void ss_updown_a35(sc_sub_t ss, sc_bool_t up); \
    void ss_prepost_power_mode_a35(sc_sub_t ss, dsc_pdom_t pd, ss_prepost_t \
        type, sc_pm_power_mode_t from_mode, sc_pm_power_mode_t to_mode, \
        sc_bool_t rom_boot); \
    void ss_link_enable_a35(sc_sub_t ss, dsc_pdom_t pd, sc_bool_t enable); \
    void ss_adb_enable_a35(sc_sub_t ss, sc_sub_t remote, sc_bool_t enable); \
    void ss_adb_wait_a35(sc_sub_t ss, sc_sub_t remote, sc_bool_t enable); \


/*!
 * This define is used to override the default SS function entry points.
 * If this isn't defined, then the SS uses functions in base.
 */
#define SS_EP_INIT_A35 \
    { \
        ss_init_a35, \
        ss_trans_power_mode_base, \
        ss_rsrc_reset_base, \
        ss_set_cpu_power_mode_a35, \
        ss_set_cpu_resume_a35, \
        ss_req_sys_if_power_mode_a35, \
        ss_set_clock_rate_a35, \
        ss_get_clock_rate_base, \
        ss_clock_enable_base, \
        ss_force_clock_enable_base, \
        ss_set_clock_parent_base, \
        ss_get_clock_parent_base, \
        ss_is_rsrc_accessible_base, \
        ss_mu_irq_base, \
        ss_cpu_start_a35, \
        ss_rdc_enable_base, \
        ss_rdc_set_master_a35, \
        ss_rdc_set_peripheral_base, \
        ss_rdc_set_memory_base, \
        ss_set_control_base, \
        ss_get_control_base, \
        ss_irq_enable_base, \
        ss_irq_status_base, \
        ss_irq_trigger_base, \
        ss_dump_base, \
        ss_do_mem_repair_base, \
        ss_updown_a35, \
        ss_prepost_power_mode_a35, \
        ss_iso_disable_base, \
        ss_link_enable_a35, \
        ss_ssi_power_base, \
        ss_ssi_bhole_mode_base, \
        ss_ssi_pause_mode_base, \
        ss_ssi_wait_idle_base, \
        ss_adb_enable_a35, \
        ss_adb_wait_a35, \
        ss_prepost_clock_mode_base, \
        ss_rdc_is_did_vld_base, \
    }

#ifdef DEBUG
    /*!
     * This define is used to name resources for debug output.
     */
    #define RNAME_INIT_A35_0 \
        "A35_0", \
        "A35_1", \
        "A35_2", \
        "A35_3", \
        "A35", \

#endif

#endif /* SC_SS_A35_CONFIG_H */

/** @} */

