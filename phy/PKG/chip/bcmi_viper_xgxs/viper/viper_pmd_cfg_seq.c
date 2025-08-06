/*
 *         
 * 
 *
 * This software is governed by the Broadcom Switch APIs license.
 * This license is set out in https://raw.githubusercontent.com/Broadcom-Network-Switching-Software/OpenMDK/master/Legal/LICENSE file.
 * 
 * Copyright 2007-2020 Broadcom Inc. All rights reserved.
 *         
 *     
 */
/*
 *  $Copyright: Copyright 2016 Broadcom Corporation.
 *  This program is the proprietary software of Broadcom Corporation
 *  and/or its licensors, and may only be used, duplicated, modified
 *  or distributed pursuant to the terms and conditions of a separate,
 *  written license agreement executed between you and Broadcom
 *  (an "Authorized License").  Except as set forth in an Authorized
 *  License, Broadcom grants no license (express or implied), right
 *  to use, or waiver of any kind with respect to the Software, and
 *  Broadcom expressly reserves all rights in and to the Software
 *  and all intellectual property rights therein.  IF YOU HAVE
 *  NO AUTHORIZED LICENSE, THEN YOU HAVE NO RIGHT TO USE THIS SOFTWARE
 *  IN ANY WAY, AND SHOULD IMMEDIATELY NOTIFY BROADCOM AND DISCONTINUE
 *  ALL USE OF THE SOFTWARE.  
 *   
 *  Except as expressly set forth in the Authorized License,
 *   
 *  1.     This program, including its structure, sequence and organization,
 *  constitutes the valuable trade secrets of Broadcom, and you shall use
 *  all reasonable efforts to protect the confidentiality thereof,
 *  and to use this information only in connection with your use of
 *  Broadcom integrated circuit products.
 *   
 *  2.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, THE SOFTWARE IS
 *  PROVIDED "AS IS" AND WITH ALL FAULTS AND BROADCOM MAKES NO PROMISES,
 *  REPRESENTATIONS OR WARRANTIES, EITHER EXPRESS, IMPLIED, STATUTORY,
 *  OR OTHERWISE, WITH RESPECT TO THE SOFTWARE.  BROADCOM SPECIFICALLY
 *  DISCLAIMS ANY AND ALL IMPLIED WARRANTIES OF TITLE, MERCHANTABILITY,
 *  NONINFRINGEMENT, FITNESS FOR A PARTICULAR PURPOSE, LACK OF VIRUSES,
 *  ACCURACY OR COMPLETENESS, QUIET ENJOYMENT, QUIET POSSESSION OR
 *  CORRESPONDENCE TO DESCRIPTION. YOU ASSUME THE ENTIRE RISK ARISING
 *  OUT OF USE OR PERFORMANCE OF THE SOFTWARE.
 *  
 *  3.     TO THE MAXIMUM EXTENT PERMITTED BY LAW, IN NO EVENT SHALL
 *  BROADCOM OR ITS LICENSORS BE LIABLE FOR (i) CONSEQUENTIAL,
 *  INCIDENTAL, SPECIAL, INDIRECT, OR EXEMPLARY DAMAGES WHATSOEVER
 *  ARISING OUT OF OR IN ANY WAY RELATING TO YOUR USE OF OR INABILITY
 *  TO USE THE SOFTWARE EVEN IF BROADCOM HAS BEEN ADVISED OF THE
 *  POSSIBILITY OF SUCH DAMAGES; OR (ii) ANY AMOUNT IN EXCESS OF
 *  THE AMOUNT ACTUALLY PAID FOR THE SOFTWARE ITSELF OR USD 1.00,
 *  WHICHEVER IS GREATER. THESE LIMITATIONS SHALL APPLY NOTWITHSTANDING
 *  ANY FAILURE OF ESSENTIAL PURPOSE OF ANY LIMITED REMEDY.$
*/


#include <phymod/phymod.h>
#include "viper_common.h" 
#include "viper_pmd_cfg_seq.h" 
#include <phymod/chip/bcmi_viper_xgxs_defs.h>


int viper_prbs_lane_inv_data_get (PHYMOD_ST *pa, 
                                  uint8_t    lane_num, 
                                  uint32_t  *inv_data)
{
    LANEPRBSr_t tmp_reg;
    int lane = 0;
    uint16_t mask = pa->lane_mask;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    LANEPRBSr_CLR(tmp_reg);
    READ_LANEPRBSr(&pa_copy, &tmp_reg);

    for (lane = 0; lane < 4; lane++, mask >>=1){
        if (mask & 0x1){ 
            switch(lane) {
                case 3:
                    *inv_data = LANEPRBSr_PRBS_INV3f_GET(tmp_reg);
                    break;
                case 2:
                    *inv_data = LANEPRBSr_PRBS_INV2f_GET(tmp_reg);
                    break;
                case 1:
                    *inv_data = LANEPRBSr_PRBS_INV1f_GET(tmp_reg);
                    break;
                case 0:
                default:
                    *inv_data = LANEPRBSr_PRBS_INV0f_GET(tmp_reg);
                    break;
            }
        }
    }

    return PHYMOD_E_NONE;
}

int viper_prbs_lane_poly_get (PHYMOD_ST *pa, 
                              uint8_t    lane_num, 
                              viper_prbs_poly_t *prbs_poly)
{
    LANEPRBSr_t tmp_reg;
    int lane = 0;
    uint16_t mask = pa->lane_mask;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    LANEPRBSr_CLR(tmp_reg);
    READ_LANEPRBSr(&pa_copy, &tmp_reg);

    for (lane = 0; lane < 4; lane++, mask >>=1) {
        if (mask & 0x1){
            switch(lane) {
                case 3:
                    *prbs_poly = LANEPRBSr_PRBS_ORDER3f_GET(tmp_reg);
                    break;
                case 2:
                    *prbs_poly = LANEPRBSr_PRBS_ORDER2f_GET(tmp_reg);
                    break;
                case 1:
                    *prbs_poly = LANEPRBSr_PRBS_ORDER1f_GET(tmp_reg);
                    break;
                case 0:
                default:
                    *prbs_poly = LANEPRBSr_PRBS_ORDER0f_GET(tmp_reg);
                    break;
            }
        }
    }

    return PHYMOD_E_NONE;
}

int viper_prbs_enable_get (PHYMOD_ST *pa, 
                           uint8_t    lane_num, 
                           uint32_t  *enable)
{
    LANEPRBSr_t tmp_reg;
    int lane = 0;
    uint16_t mask = pa->lane_mask;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    LANEPRBSr_CLR(tmp_reg);
    READ_LANEPRBSr(&pa_copy, &tmp_reg);

    for (lane = 0; lane < 4 ; lane++, mask >>= 1) {
        if (mask & 0x1){
            switch(lane) {
                case 3:
                    *enable = LANEPRBSr_PRBS_EN3f_GET(tmp_reg);
                    break;
                case 2:
                    *enable = LANEPRBSr_PRBS_EN2f_GET(tmp_reg);
                    break;
                case 1:
                    *enable = LANEPRBSr_PRBS_EN1f_GET(tmp_reg);
                    break;
                case 0:
                default:
                    *enable = LANEPRBSr_PRBS_EN0f_GET(tmp_reg);
                     break;
            }
        }
    }

    return PHYMOD_E_NONE;
}

int viper_prbs_lane_inv_data_set (PHYMOD_ST *pa, 
                                  uint8_t    lane_num, 
                                  uint32_t   inv_data)
{
    LANEPRBSr_t tmp_reg;
    int lane = 0;
    uint16_t mask = pa->lane_mask;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    LANEPRBSr_CLR(tmp_reg);
    READ_LANEPRBSr(&pa_copy, &tmp_reg);
    for (lane = 0; lane < 4; lane++, mask >>= 1){
        if (mask & 0x1){    
            switch(lane) {
                case 3:
                    LANEPRBSr_PRBS_INV3f_SET(tmp_reg, inv_data);
                    break;
                case 2:
                    LANEPRBSr_PRBS_INV2f_SET(tmp_reg, inv_data);
                    break;
                case 1:
                    LANEPRBSr_PRBS_INV1f_SET(tmp_reg, inv_data);
                    break;
                case 0:
                default:
                    LANEPRBSr_PRBS_INV0f_SET(tmp_reg, inv_data);
                    break;
             }
             MODIFY_LANEPRBSr(&pa_copy, tmp_reg);
        }
    }

    MODIFY_LANEPRBSr(pa, tmp_reg);
    return PHYMOD_E_NONE;
}

int viper_prbs_lane_poly_set (PHYMOD_ST *pa, 
                              uint8_t    lane_num, 
                              viper_prbs_poly_t prbs_poly)
{
    LANEPRBSr_t tmp_reg;
    int lane = 0;
    uint16_t mask = pa->lane_mask;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    LANEPRBSr_CLR(tmp_reg);
    READ_LANEPRBSr(pa, &tmp_reg);

    for (lane = 0; lane < 4; lane++, mask >>=1){
        if (mask & 0x1){
            switch(lane) {
                case 3:
                    LANEPRBSr_PRBS_ORDER3f_SET(tmp_reg, prbs_poly);
                    break;
                case 2:
                    LANEPRBSr_PRBS_ORDER2f_SET(tmp_reg, prbs_poly);
                    break;
                case 1:
                    LANEPRBSr_PRBS_ORDER1f_SET(tmp_reg, prbs_poly);
                    break;
                case 0:
                default:
                    LANEPRBSr_PRBS_ORDER0f_SET(tmp_reg, prbs_poly);
                    break;
            }
            MODIFY_LANEPRBSr(&pa_copy, tmp_reg);
        }
    }

    return PHYMOD_E_NONE;
}

/*
 * viper_prbs_enable_set
 *
 * Disable CL36      0x8015 : 0x0000
 * Set 1G Mode       0x8016 : 0x0000
 * Disable cden/eden 0x8017 : 0x0000
 * set prbs order    0x8019 : 0x3333
 * enable prbs       0x8019 : 0xBBBB
 * choose tx datai   0x815A : 0x00F0
 * Broadcast         0xFFDE : 0x001F
 * OS2/0s5           0x834A : 0x000X
 *
 */

int viper_prbs_enable_set (PHYMOD_ST *pa, 
                           uint8_t    lane_num, 
                           uint32_t   enable)
{
    LANEPRBSr_t tmp_reg;
    LANECTL0r_t      lane_ctl0;
    LANECTL1r_t      lane_ctl1;
    LANECTL2r_t      lane_ctl2;
    PRBS_DECOUPLEr_t  prbs_reg;
    AERr_t           aereg;
    DIG_MISC8r_t      misc8;
    int os_mode = VIPER_MISC8_OSDR_MODE_OSX5;
    int lane = 0;
    uint16_t sgmii_mode = 0;
    uint16_t  mask = pa->lane_mask;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    LANEPRBSr_CLR(tmp_reg);
    PRBS_DECOUPLEr_CLR(prbs_reg);
    AERr_CLR(aereg);
    DIG_MISC8r_CLR(misc8);

    /* Disable CL36 */
    READ_LANECTL0r(&pa_copy, &lane_ctl0);
    LANECTL0r_CL36_PCS_EN_RXf_SET(lane_ctl0, enable? 0 : 0xf);
    LANECTL0r_CL36_PCS_EN_TXf_SET(lane_ctl0, enable? 0 : 0xf);
    WRITE_LANECTL0r(&pa_copy, lane_ctl0);

    /* Set 1G mode */
    LANECTL1r_CLR(lane_ctl1);
    WRITE_LANECTL1r(&pa_copy, lane_ctl1);

    /* Disable cden/eden */
    READ_LANECTL2r(&pa_copy, &lane_ctl2);
    LANECTL2r_EDEN1Gf_SET(lane_ctl2, enable? 0 : 0xf);
    LANECTL2r_CDET_EN1Gf_SET(lane_ctl2, enable? 0 : 0xf);
    WRITE_LANECTL2r(&pa_copy, lane_ctl2);

    /* Enable prbs*/
    READ_LANEPRBSr(&pa_copy, &tmp_reg);
    for (lane = 0; lane < 4; lane++, mask >>= 1){
        if (mask & 0x1){
            switch(lane) {
                case 3:
                    LANEPRBSr_PRBS_EN3f_SET(tmp_reg, enable);
                    break;
                case 2:
                    LANEPRBSr_PRBS_EN2f_SET(tmp_reg, enable);
                    break;
                case 1:
                    LANEPRBSr_PRBS_EN1f_SET(tmp_reg, enable);
                    break;
                case 0:
                default:
                    LANEPRBSr_PRBS_EN0f_SET(tmp_reg, enable);
                    break;
            }
            MODIFY_LANEPRBSr(&pa_copy, tmp_reg);
        }
    }

    /* Choose tx_datai*/
    PRBS_DECOUPLEr_TX_DATAI_PRBS_SEL_0f_SET(prbs_reg, enable);
    PRBS_DECOUPLEr_TX_DATAI_PRBS_SEL_1f_SET(prbs_reg, enable);
    PRBS_DECOUPLEr_TX_DATAI_PRBS_SEL_2f_SET(prbs_reg, enable);
    PRBS_DECOUPLEr_TX_DATAI_PRBS_SEL_3f_SET(prbs_reg, enable);
    WRITE_PRBS_DECOUPLEr(&pa_copy, prbs_reg);

    /* Broadcast */
    AERr_MMD_PORTf_SET(aereg, enable? 0x1ff : 0x0);
    MODIFY_AERr(&pa_copy, aereg);

    /* Set os2/os5 mode */
    viper_sgmii_mode_get(pa, &sgmii_mode);
    if(!sgmii_mode){
      os_mode = VIPER_MISC8_OSDR_MODE_OSX2; 
    }
    DIG_MISC8r_FORCE_OSCDR_MODEf_SET(misc8, os_mode);
    MODIFY_DIG_MISC8r(pa, misc8);

    return PHYMOD_E_NONE;
}


int viper_prbs_status_get (PHYMOD_ST *pa, viper_prbs_status_t *status)
{
    RX_AFE_ANARXCTLr_t   ctl;
    RX_AFE_ANARXCTL1Gr_t ctl1g;
    RX_AFE_ANARXSTSr_t   stsreg;
    uint32_t value;  
 
    RX_AFE_ANARXSTSr_CLR(stsreg);

    /* Select prbs_status */
    READ_RX_AFE_ANARXCTLr(pa, &ctl); 
    RX_AFE_ANARXCTLr_STATUS_SELf_SET(ctl, 0x7); 
    WRITE_RX_AFE_ANARXCTLr(pa, ctl); 

    /* Disable |E| moniter */
    READ_RX_AFE_ANARXCTL1Gr(pa, &ctl1g);  
    RX_AFE_ANARXCTL1Gr_EMON_ENf_SET(ctl1g, 0x0);
    WRITE_RX_AFE_ANARXCTL1Gr(pa, ctl1g);  

    /* Read prbs status */ 
    READ_RX_AFE_ANARXSTSr(pa, &stsreg);
    value = RX_AFE_ANARXSTSr_GET(stsreg);
    status->prbs_lock = (value >> 15) & 0x1;
    status->prbs_lock_loss = (value >> 14) & 0x1; 
    status->error_count = value & 0x3F;

    return PHYMOD_E_NONE;
}


/* tx lane reset */
int viper_tx_lane_reset (PHYMOD_ST *pa, 
                         uint32_t  enable)   
{
    LANERESETr_t reg_lane_reset;

    LANERESETr_CLR           (reg_lane_reset);
    LANERESETr_RESET_TXf_SET (reg_lane_reset, enable);
    MODIFY_LANERESETr        (pa,  reg_lane_reset);

    return PHYMOD_E_NONE;
}

/* rx lane reset */
int viper_rx_lane_reset (PHYMOD_ST *pa, 
                         uint32_t  enable)   
{
    LANERESETr_t reg_lane_reset;

    LANERESETr_CLR           (reg_lane_reset);
    LANERESETr_RESET_RXf_SET (reg_lane_reset, enable);
    MODIFY_LANERESETr        (pa,  reg_lane_reset);

    return PHYMOD_E_NONE;
}

/* pll reset */
int viper_pll_reset (const PHYMOD_ST *pa, 
                     uint32_t  enable)   
{
    LANERESETr_t reg_lane_reset;

    LANERESETr_CLR           (reg_lane_reset);
    LANERESETr_RESET_PLLf_SET(reg_lane_reset, enable);
    MODIFY_LANERESETr        (pa,  reg_lane_reset);

    return PHYMOD_E_NONE;
}

/* mdio reset */
int viper_mdio_reset (PHYMOD_ST *pa, 
                      uint32_t  enable)   
{
    LANERESETr_t reg_lane_reset;

    LANERESETr_CLR            (reg_lane_reset);
    LANERESETr_RESET_MDIOf_SET(reg_lane_reset, enable);
    MODIFY_LANERESETr         (pa,  reg_lane_reset);

    return PHYMOD_E_NONE;
}


int viper_pmd_force_ana_signal_detect (PHYMOD_ST *pa, int enable)   
{
    RX_AFE_ANARXSIGDETr_t reg;

    RX_AFE_ANARXSIGDETr_CLR(reg);
    RX_AFE_ANARXSIGDETr_RX_SIGDET_Rf_SET(reg, enable);
    RX_AFE_ANARXSIGDETr_RX_SIGDET_FORCE_Rf_SET(reg, enable);

    MODIFY_RX_AFE_ANARXSIGDETr(pa, reg);

    return PHYMOD_E_NONE;
}

int viper_mii_gloop_get(PHYMOD_ST *pa, uint32_t *enable)   
{
    LANECTL2r_t reg;

    READ_LANECTL2r(pa, &reg);

    *enable = LANECTL2r_GLOOP1Gf_GET(reg);

    return PHYMOD_E_NONE;
}

int viper_mii_gloop_set(PHYMOD_ST *pa, uint32_t enable)   
{
    LANECTL2r_t reg;

    READ_LANECTL2r(pa, &reg);
    LANECTL2r_GLOOP1Gf_SET(reg, enable);
    MODIFY_LANECTL2r(pa, reg);

    return PHYMOD_E_NONE;
}

int viper_pll_disable(const PHYMOD_ST *pa)
{
    XGXSCTLr_t reg;

    XGXSCTLr_CLR(reg);
    /* READ_XGXSCTLr(pa, &reg); */

    /* Disable PLL 0x8000 : 0x052F */
    XGXSCTLr_EDENf_SET      (reg, 1);
    XGXSCTLr_CDET_ENf_SET   (reg, 1);
    XGXSCTLr_AFRST_ENf_SET  (reg, 1);
    XGXSCTLr_TXCKO_DIVf_SET (reg, 1);
    XGXSCTLr_RESERVED_5f_SET(reg, 1);
    XGXSCTLr_MODEf_SET      (reg, VIPER_XGXS_MODE_INDLANE_OS5);

    WRITE_XGXSCTLr(pa, reg);
    return PHYMOD_E_NONE;
}

int viper_pll_disable_forced_10G(PHYMOD_ST *pa)
{
    XGXSCTLr_t reg;

    XGXSCTLr_CLR(reg);

    /* Disable PLL 0x8000 : 0x0C2F */
    XGXSCTLr_EDENf_SET      (reg, 1);
    XGXSCTLr_CDET_ENf_SET   (reg, 1);
    XGXSCTLr_AFRST_ENf_SET  (reg, 1);
    XGXSCTLr_TXCKO_DIVf_SET (reg, 1);
    XGXSCTLr_RESERVED_5f_SET(reg, 1);
    XGXSCTLr_MODEf_SET      (reg, VIPER_XGXS_MODE_COMBO_CORE);

    MODIFY_XGXSCTLr(pa, reg);
    return PHYMOD_E_NONE;
}

/*
 * viper_link_enable_sm
 * Set link_en_r[4] = 1;
 */
int viper_link_enable_sm_reset (const PHYMOD_ST *pa)
{
    RX_AFE_ANARXCTLPCIr_t pci_reg;

    READ_RX_AFE_ANARXCTLPCIr(pa, &pci_reg);
    RX_AFE_ANARXCTLPCIr_LINK_EN_Rf_SET(pci_reg, 1);
    WRITE_RX_AFE_ANARXCTLPCIr(pa, pci_reg);

    return PHYMOD_E_NONE;
}


int viper_pll_enable(const PHYMOD_ST *pa)
{
    XGXSCTLr_t reg;

    XGXSCTLr_CLR(reg);
    /*READ_XGXSCTLr(pa, &reg); */

    /* Enable PLL 0x8000 : 0x253F */
    XGXSCTLr_START_SEQUENCERf_SET (reg, 1);
    XGXSCTLr_MODEf_SET            (reg, VIPER_XGXS_MODE_INDLANE_OS5);
    XGXSCTLr_RESERVED_5f_SET      (reg, 1);
    XGXSCTLr_MDIO_CONT_ENf_SET    (reg, 1);
    XGXSCTLr_CDET_ENf_SET         (reg, 1);
    XGXSCTLr_EDENf_SET            (reg, 1);
    XGXSCTLr_AFRST_ENf_SET        (reg, 1);
    XGXSCTLr_TXCKO_DIVf_SET       (reg, 1);

    WRITE_XGXSCTLr(pa, reg);
       
     
    viper_link_enable_sm_reset(pa);

    return PHYMOD_E_NONE;
}

int viper_pll_enable_forced_10G(PHYMOD_ST *pa)
{
    XGXSCTLr_t reg;

    XGXSCTLr_CLR(reg);

    /* Disable PLL 0x8000 : 0x2C2F */
    XGXSCTLr_START_SEQUENCERf_SET (reg, 1);
    XGXSCTLr_MODEf_SET            (reg, VIPER_XGXS_MODE_COMBO_CORE);
    XGXSCTLr_EDENf_SET            (reg, 1);
    XGXSCTLr_CDET_ENf_SET         (reg, 1);
    XGXSCTLr_AFRST_ENf_SET        (reg, 1);
    XGXSCTLr_TXCKO_DIVf_SET       (reg, 1);
    XGXSCTLr_RESERVED_5f_SET      (reg, 1);

    MODIFY_XGXSCTLr(pa, reg);
    return PHYMOD_E_NONE;
}


/* 
 * viper_sgmii_force_speed 
 *
 * Set SGMII Mode   0x8300: 0x0100 (four)
 * Set 10M & Dis AN 0x0000: 0x0100 (one)
 * Set OS 5 Mode    0x834A: 0x0003 (four)
 *
 */
static int viper_sgmii_force_speed (PHYMOD_ST *pa, uint8_t speed)
{

    DIG_CTL1000X1r_t  x1reg; 
    MIICTLr_t         miictrl;
    DIG_MISC8r_t      misc8; 
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;


    /* Clear Registers */
    DIG_CTL1000X1r_CLR(x1reg);
    MIICTLr_CLR(miictrl);
    DIG_MISC8r_CLR(misc8);
    
    /* Bit 0 is SGMII Mode */
    DIG_CTL1000X1r_COMMA_DET_ENf_SET(x1reg, 1);
    DIG_CTL1000X1r_FIBER_MODE_1000Xf_SET(x1reg,0);
    MODIFY_DIG_CTL1000X1r(pa, x1reg);

    /* Set 10M, Dis AN */
    MIICTLr_AUTONEG_ENABLEf_SET(miictrl, 0);
    MIICTLr_MANUAL_SPEED0f_SET (miictrl, speed&0x1);
    MIICTLr_MANUAL_SPEED1f_SET (miictrl, speed&0x2?1:0);
    MIICTLr_FULL_DUPLEXf_SET   (miictrl, 1);
    WRITE_MIICTLr(pa, miictrl);

    /* Set os5 mode */
    DIG_MISC8r_FORCE_OSCDR_MODEf_SET(misc8, VIPER_MISC8_OSDR_MODE_OSX5);
    WRITE_DIG_MISC8r(pa, misc8);

    return PHYMOD_E_NONE;
}


/* 
 * viper_sgmii_force_10m 
 *
 * Set SGMII Mode   0x8300: 0x0100
 * Set 10M & Dis AN 0x0000: 0x0100
 * Set OS 5 Mode    0x834A: 0x0003
 *
 */
int viper_sgmii_force_10m (PHYMOD_ST *pa)
{
    return (viper_sgmii_force_speed (pa, VIPER_SPD_10_SGMII));
}


/* 
 * viper_sgmii_force_100m 
 *
 * Set SGMII Mode   0x8300: 0x0100
 * Set 10M & Dis AN 0x0000: 0x2100
 * Set OS 5 Mode    0x834A: 0x0003
 *
 */
int viper_sgmii_force_100m (PHYMOD_ST *pa)
{
    return (viper_sgmii_force_speed (pa, VIPER_SPD_100_SGMII));
}


/* 
 * viper_sgmii_force_1G 
 *
 * Set SGMII Mode   0x8300: 0x0100
 * Set 10M & Dis AN 0x0000: 0x0140
 * Set OS 5 Mode    0x834A: 0x0003
 *
 */
int viper_sgmii_force_1g (PHYMOD_ST *pa)
{
    return (viper_sgmii_force_speed (pa, VIPER_SPD_1000_SGMII));
}


/* 
 * viper_fiber_force_100FX 
 *
 * Set Fiber Mode   0x8300: 0x0005
 * Set OS 5 Mode    0x834A: 0x0003
 * Set FX Mode      0x8400: 0x014B
 * Dis Idle Correla 0x8402: 0x0880
 *
 */
int viper_fiber_force_100FX (PHYMOD_ST *pa)
{
    DIG_CTL1000X1r_t  x1reg;
    DIG_MISC8r_t      misc8;
    FX100_CTL1r_t     fxctrl;
    FX100_CTL2r_t     ctrl2;
    FX100_CTL3r_t     ctrl3;

    /* Clear Registers */
    DIG_CTL1000X1r_CLR(x1reg);
    FX100_CTL1r_CLR(fxctrl);
    FX100_CTL2r_CLR(ctrl2);
    FX100_CTL3r_CLR(ctrl3);
    DIG_MISC8r_CLR(misc8);

    /* Bit 0 is Fiber Mode */
    DIG_CTL1000X1r_FIBER_MODE_1000Xf_SET(x1reg, 1);
    /*DIG_CTL1000X1r_SIGNAL_DETECT_ENf_SET(x1reg, 1);*/
    DIG_CTL1000X1r_COMMA_DET_ENf_SET(x1reg, 0);
    MODIFY_DIG_CTL1000X1r(pa, x1reg);

    /* Set os5 mode */
    DIG_MISC8r_FORCE_OSCDR_MODEf_SET(misc8, VIPER_MISC8_OSDR_MODE_OSX5);
    MODIFY_DIG_MISC8r(pa, misc8);

    /* Set FX Mode, Disable Idle Correlator */ 
    FX100_CTL1r_RXDATA_SELf_SET(fxctrl, 5);
    FX100_CTL1r_FAR_END_FAULT_ENf_SET(fxctrl, 1);
    FX100_CTL1r_FULL_DUPLEXf_SET(fxctrl, 1);
    FX100_CTL1r_ENABLEf_SET(fxctrl, 1);
    MODIFY_FX100_CTL1r(pa, fxctrl);

    /* Allow reception of extended length packets */
    FX100_CTL2r_EXTEND_PKT_SIZEf_SET(ctrl2, 1);
    MODIFY_FX100_CTL2r(pa, ctrl2);

    FX100_CTL3r_NUMBER_OF_IDLEf_SET(ctrl3, 8);
    FX100_CTL3r_CORRELATOR_DISABLEf_SET(ctrl3, 1);
    MODIFY_FX100_CTL3r(pa, ctrl3);

    return PHYMOD_E_NONE;
}

/* 
 * viper_fiber_force_1G 
 *
 * Set Fiber Mode   0x8300: 0x0101
 * Set 1G, Dis AN   0x0000: 0x0140
 * Set OS 5 Mode    0x834A: 0x0003
 *
 */
int viper_fiber_force_1G (PHYMOD_ST *pa)
{
    DIG_CTL1000X1r_t  x1reg;
    MIICTLr_t         miictrl;
    DIG_MISC8r_t      misc8;

    /* Clear Registers */
    DIG_CTL1000X1r_CLR(x1reg);
    MIICTLr_CLR(miictrl);
    DIG_MISC8r_CLR(misc8);

    /* Bit 0 is Fiber Mode */
    DIG_CTL1000X1r_FIBER_MODE_1000Xf_SET(x1reg, 1);
    /*DIG_CTL1000X1r_SIGNAL_DETECT_ENf_SET(x1reg, 1);*/
    DIG_CTL1000X1r_COMMA_DET_ENf_SET(x1reg, 1);
    MODIFY_DIG_CTL1000X1r(pa, x1reg);

    /* Set 1G, Dis AN */
    MIICTLr_AUTONEG_ENABLEf_SET(miictrl, 0);
    MIICTLr_MANUAL_SPEED1f_SET (miictrl, VIPER_SPD_1000_SGMII>>1);
    MIICTLr_MANUAL_SPEED0f_SET (miictrl, VIPER_SPD_1000_SGMII&1);
    MIICTLr_FULL_DUPLEXf_SET   (miictrl, 1);
    MODIFY_MIICTLr(pa, miictrl);

    /* Set os5 mode */
    DIG_MISC8r_FORCE_OSCDR_MODEf_SET(misc8, VIPER_MISC8_OSDR_MODE_OSX5);
    MODIFY_DIG_MISC8r(pa, misc8);

    return PHYMOD_E_NONE;
}

/* 
 * viper_fiber_force_2p5G 
 *
 * Set Fiber Mode   0x8300: 0x0105
 * Set 2.5G         0x8308: 0xC010
 * Set OS 5 Mode    0x834A: 0x0001
 *
 */
int viper_fiber_force_2p5G (PHYMOD_ST *pa)
{
    DIG_CTL1000X1r_t  x1reg;
    DIG_MISC1r_t      misc1;
    DIG_MISC8r_t      misc8;

    /* Clear Registers */
    DIG_CTL1000X1r_CLR(x1reg);
    DIG_MISC1r_CLR(misc1);
    DIG_MISC8r_CLR(misc8);

    /* Bit 0 is Fiber Mode */
    DIG_CTL1000X1r_FIBER_MODE_1000Xf_SET(x1reg, 1);
    /*DIG_CTL1000X1r_SIGNAL_DETECT_ENf_SET(x1reg, 1);*/
    DIG_CTL1000X1r_COMMA_DET_ENf_SET(x1reg, 1);
    MODIFY_DIG_CTL1000X1r(pa, x1reg);

    DIG_MISC1r_REFCLK_SELf_SET (misc1, VIPER_MISC1_CLK_50M); /* clk_50Mhz */
    DIG_MISC1r_FORCE_SPEEDf_SET(misc1, VIPER_MISC1_2500BRCM_X1);  /* 2500BRCM_X1 */ 

    MODIFY_DIG_MISC1r(pa, misc1);

    /* Set os2 mode */
    DIG_MISC8r_FORCE_OSCDR_MODEf_SET(misc8, VIPER_MISC8_OSDR_MODE_OSX2);
    MODIFY_DIG_MISC8r(pa, misc8);

    return PHYMOD_E_NONE;
}


/* 
 * viper_fiber_force_speed 
 *
 * Set Lane Broadcast         0xFFD0: 0x001F
 * Set Fiber Mode             0x8300: 0x0105
 * Set SPEED                  0x8308: 0x601X
 * Set OS 2 Mode              0x834A: 0x0001
 * Enable clock compensation  0x8104: 0x0000
 *
 */
static int viper_fiber_force_speed (PHYMOD_ST *pa, uint8_t speed)
{
    AERr_t aereg;
    DIG_CTL1000X1r_t  x1reg;
    DIG_MISC1r_t      misc1;
    DIG_MISC8r_t      misc8;
    UNICOREMODE10Gr_t  unireg; 
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;


    /* Clear Registers */
    AERr_CLR(aereg);
    DIG_CTL1000X1r_CLR(x1reg);
    DIG_MISC1r_CLR(misc1);
    DIG_MISC8r_CLR(misc8);

    /* Broadcast */    
    AERr_MMD_PORTf_SET(aereg, 0x1ff);  
    MODIFY_AERr(&pa_copy, aereg);

    /* Bit 0 is Fiber Mode */
    DIG_CTL1000X1r_FIBER_MODE_1000Xf_SET(x1reg, 1);
    DIG_CTL1000X1r_SIGNAL_DETECT_ENf_SET(x1reg, 1);
    DIG_CTL1000X1r_COMMA_DET_ENf_SET(x1reg, 1);
    MODIFY_DIG_CTL1000X1r(&pa_copy, x1reg);

    /* Set Speed */
    DIG_MISC1r_REFCLK_SELf_SET(misc1, VIPER_MISC1_CLK_156p25M); /* clk_156.25Mhz */
    DIG_MISC1r_FORCE_SPEEDf_SET(misc1, speed);
    MODIFY_DIG_MISC1r(&pa_copy, misc1);

    /* Set os2 mode */
    DIG_MISC8r_FORCE_OSCDR_MODEf_SET(misc8, VIPER_MISC8_OSDR_MODE_OSX2);
    MODIFY_DIG_MISC8r(&pa_copy, misc8);

    /* Enabled clock compensation */
    READ_UNICOREMODE10Gr(&pa_copy, &unireg);
    UNICOREMODE10Gr_UNICOREMODE10GCX4f_SET(unireg, 0x0);
    WRITE_UNICOREMODE10Gr(&pa_copy, unireg);


    return PHYMOD_E_NONE;
}

/* 
 * viper_fiber_force_10G 
 *
 * Set Lane Broadcast 0xFFD0: 0x001F
 * Set Fiber Mode     0x8300: 0x0105
 * Set 10G            0x8318: 0x6013
 * Set OS 2 Mode      0x834A: 0x0001
 *
 */
int viper_fiber_force_10G (PHYMOD_ST *pa)
{
    /*return (viper_fiber_force_speed (pa, VIPER_MISC1_10GHiGig_X4));*/
    return PHYMOD_E_NONE;
}

/* 
 * viper_fiber_force_10G_CX4 
 *
 * Set Lane Broadcast 0xFFD0: 0x001F
 * Set Fiber Mode     0x8300: 0x0105
 * Set 10G            0x8318: 0x6014
 * Set OS 2 Mode      0x834A: 0x0001
 *
 */
int viper_fiber_force_10G_CX4 (PHYMOD_ST *pa)
{
    return (viper_fiber_force_speed (pa, VIPER_MISC1_10GBASE_CX4));
}

/* 
 * viper_fiber_AN_1G 
 *
 * Set Fiber Mode     0x8300: 0x0141
 * Set OS 5 Mode      0x834A: 0x0003
 * Set 1G             0x8000: 0x1140
 *
 */
int viper_fiber_AN_1G (const PHYMOD_ST *pa)
{
    DIG_CTL1000X1r_t  x1reg;
    DIG_MISC8r_t      misc8;
    MIICTLr_t         miictrl;

    /* Clear Registers */
    DIG_CTL1000X1r_CLR(x1reg);
    DIG_MISC8r_CLR(misc8);
    MIICTLr_CLR(miictrl);

    /* Fiber Mode, sig det, dis pll pwrdn, comma det */
    DIG_CTL1000X1r_FIBER_MODE_1000Xf_SET(x1reg, 1);
    /*DIG_CTL1000X1r_SIGNAL_DETECT_ENf_SET(x1reg, 1);*/
    DIG_CTL1000X1r_DISABLE_PLL_PWRDWNf_SET(x1reg, 1);
    DIG_CTL1000X1r_COMMA_DET_ENf_SET(x1reg, 1);
    MODIFY_DIG_CTL1000X1r(pa, x1reg);

    /* Set os5 mode */
    DIG_MISC8r_FORCE_OSCDR_MODEf_SET(misc8, VIPER_MISC8_OSDR_MODE_OSX5);
    MODIFY_DIG_MISC8r(pa, misc8);

    /* AN, FD, 1G */
    MIICTLr_AUTONEG_ENABLEf_SET(miictrl, 1);
    MIICTLr_MANUAL_SPEED0f_SET (miictrl, VIPER_SPD_1000_SGMII&1);
    MIICTLr_MANUAL_SPEED1f_SET (miictrl, VIPER_SPD_1000_SGMII>>1);
    MIICTLr_FULL_DUPLEXf_SET   (miictrl, 1);
    MODIFY_MIICTLr(pa, miictrl);

    return PHYMOD_E_NONE;
}


/* 
 * viper_sgmii_aneg_speed 
 *
 * Set Fiber Mode     0x8300: 0x01X0 (four)
 * Set OS 5 Mode      0x834A: 0x0003 (four)
 * Set SPEED          0x0000: 0xXXXX (four)
 *
 */
static int viper_sgmii_aneg_speed (const PHYMOD_ST *pa, uint8_t master, uint8_t speed)
{
    DIG_CTL1000X1r_t  x1reg;
    DIG_MISC8r_t      misc8;
    MIICTLr_t         miictrl;

    /* Clear Registers */
    DIG_CTL1000X1r_CLR(x1reg);
    DIG_MISC8r_CLR(misc8);
    MIICTLr_CLR(miictrl);

    /* SGMII Master Mode, comma det */
    DIG_CTL1000X1r_SGMII_MASTER_MODEf_SET(x1reg, master);
    DIG_CTL1000X1r_FIBER_MODE_1000Xf_SET(x1reg, 0);
    DIG_CTL1000X1r_COMMA_DET_ENf_SET(x1reg, 1);

    MODIFY_DIG_CTL1000X1r(pa, x1reg);

    /* Set os5 mode */
    DIG_MISC8r_FORCE_OSCDR_MODEf_SET(misc8, VIPER_MISC8_OSDR_MODE_OSX5);
    MODIFY_DIG_MISC8r(pa, misc8);

    /* AN, FD, 100M */
    MIICTLr_AUTONEG_ENABLEf_SET(miictrl, 1);
    MIICTLr_MANUAL_SPEED0f_SET (miictrl, speed&1);
    MIICTLr_FULL_DUPLEXf_SET   (miictrl, 1);
    MIICTLr_MANUAL_SPEED1f_SET (miictrl, speed>>1);
    MODIFY_MIICTLr(pa, miictrl);

    return PHYMOD_E_NONE;
}

/* 
 * viper_sgmii_master_aneg_100M 
 *
 * Set Fiber Mode     0x8300: 0x0120
 * Set OS 5 Mode      0x834A: 0x0003
 * Set SPEED          0x0000: 0x3100
 *
 */
int viper_sgmii_master_aneg_100M (const PHYMOD_ST *pa, uint8_t speed)
{
    return(viper_sgmii_aneg_speed (pa, 1, VIPER_SPD_100_SGMII));
}

/* 
 * viper_sgmii_master_aneg_10M 
 *
 * Set Fiber Mode     0x8300: 0x0120
 * Set OS 5 Mode      0x834A: 0x0003
 * Set SPEED          0x0000: 0x1100
 *
 */
int viper_sgmii_aneg_10M (const PHYMOD_ST *pa)
{
    return(viper_sgmii_aneg_speed (pa, 1, VIPER_SPD_10_SGMII));
}

/* 
 * viper_sgmii_slave_aneg_speed 
 *
 * Set Fiber Mode     0x8300: 0x0100
 * Set OS 5 Mode      0x834A: 0x0003
 * Set SPEED          0x0000: 0x1140
 *
 */
int viper_sgmii_slave_aneg_speed (const PHYMOD_ST *pa)
{
    return(viper_sgmii_aneg_speed (pa, 0, VIPER_SPD_1000_SGMII));
}


/* 
 * viper_lane_reset 
 *
 * Reset lane 0x810A: 0x00FF
 *
 */
int viper_lane_reset (const PHYMOD_ST *pa)
{
    LANERESETr_t reg;

    LANERESETr_CLR(reg); 
    LANERESETr_RESET_TXf_SET(reg, 0xF);
    LANERESETr_RESET_RXf_SET(reg, 0xF);
    MODIFY_LANERESETr(pa, reg);

    return PHYMOD_E_NONE;
}

/* 
 * viper_lpi_disable 
 *
 * Disable LPI CL48  0x8150: 0x0000
 * Disable LPI CL36  0x833E: 0x0000
 *
 */
int viper_lpi_disable (const PHYMOD_ST *pa)
{
    EEECTLr_t reg;
    DIG_MISC5r_t      misc5;

    /* Clear registers */
    EEECTLr_CLR(reg); 
    DIG_MISC5r_CLR(misc5);

    EEECTLr_LPI_EN_RXf_SET(reg, 0);
    EEECTLr_LPI_EN_TXf_SET(reg, 0);
    MODIFY_EEECTLr(pa, reg);

    DIG_MISC5r_LPI_EN_RXf_SET(misc5, 0);
    DIG_MISC5r_LPI_EN_TXf_SET(misc5, 0);
    MODIFY_DIG_MISC5r(pa, misc5);

    return PHYMOD_E_NONE;
}

/* 
 * viper_global_loopback_ena 
 *
 * Enable Gloop     0x8017: 0xFF0F (one)
 * POWRDN peak/zero 0x80B0: 0xB001 (four) 
 * ForceRXSeqDone   0x80B1: 0x1C50 (four) 
 * GloopOutDis      0x8061: 0x200  (four)
 *
 */
int viper_global_loopback_set (const PHYMOD_ST *pa, uint8_t enable)
{

    LANECTL2r_t     ctl2;
    /*RX_AFE_CTL1r_t  ctl1; */
    RX_AFE_ANARXCTLr_t ctl;
    TX_AFE_ANATXACTL0r_t  reg;
    uint8_t lane_ena = 0;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1; 


    READ_LANECTL2r(&pa_copy, &ctl2);
    if(enable){
        lane_ena = (pa->lane_mask | LANECTL2r_GLOOP1Gf_GET(ctl2));
        LANECTL2r_GLOOP1Gf_SET(ctl2, lane_ena); 
    } else {
        lane_ena = (~(pa->lane_mask) & LANECTL2r_GLOOP1Gf_GET(ctl2));
        LANECTL2r_GLOOP1Gf_SET(ctl2, lane_ena);
    }
    WRITE_LANECTL2r(&pa_copy, ctl2); 

    READ_RX_AFE_ANARXCTLr(pa, &ctl);
    RX_AFE_ANARXCTLr_FORCERXSEQDONE_SMf_SET(ctl, 1);
    WRITE_RX_AFE_ANARXCTLr(pa, ctl);
#if 0
    READ_RX_AFE_CTL1r(pa, &ctl1);
    RX_AFE_CTL1r_DEMUX_PEAK_PDf_SET(ctl1, 1); 
    RX_AFE_CTL1r_DEMUX_ZERO_PDf_SET(ctl1, 1);
    WRITE_RX_AFE_CTL1r(pa, ctl1);
#endif

    READ_TX_AFE_ANATXACTL0r(pa, &reg);
    TX_AFE_ANATXACTL0r_GLOOPOUTDISf_SET(reg, enable);
    WRITE_TX_AFE_ANATXACTL0r(pa, reg);
 
    return PHYMOD_E_NONE;
}

/* 
 * viper_global_loopback_get 
 *
 * Gloop     0x8017: 0xFF0F (one)
 */
int viper_global_loopback_get (const PHYMOD_ST *pa, uint32_t *lpbk) 
{
    LANECTL2r_t   ctrl;
    uint32_t lane_lpbk = 0;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1; 

    LANECTL2r_CLR (ctrl);
    READ_LANECTL2r(&pa_copy, &ctrl);

    lane_lpbk = LANECTL2r_GLOOP1Gf_GET(ctrl);
    *lpbk = (lane_lpbk & pa->lane_mask); 
    return PHYMOD_E_NONE;
}

/* 
 * viper_remote_loopback_set
 *
 * Set remote loop 0x8000: bit 6 : 10G
 * Set remote loop 0x8300: bit 10 :1G/100M/10M
 *
 */
int viper_remote_loopback_set (const PHYMOD_ST *pa, viper_actual_speed_id_t speed_id, uint8_t enable)
{
    DIG_CTL1000X1r_t    x1reg;
    XGXSCTLr_t          xctrl;
    DIG_MISC2r_t        misc2;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    /* Clear Registers */
    READ_DIG_CTL1000X1r(pa, &x1reg);
    READ_XGXSCTLr(&pa_copy, &xctrl);
    READ_DIG_MISC2r(pa, &misc2);

    if (speed_id == VIPER_SPD_10G_CX4){
        XGXSCTLr_RLOOPf_SET(xctrl, enable);
        MODIFY_XGXSCTLr(&pa_copy, xctrl);
    } else if (speed_id <= VIPER_SPD_2p5G){
        DIG_CTL1000X1r_REMOTE_LOOPBACKf_SET(x1reg, enable);
        MODIFY_DIG_CTL1000X1r(pa, x1reg);
        if (speed_id <= VIPER_SPD_100M ){
           DIG_MISC2r_RESERVED_14_13f_SET(misc2, enable? 0x3 : 0x1);
           MODIFY_DIG_MISC2r(pa, misc2);
        }
    }
    return PHYMOD_E_NONE;
}

/*
 * viper_remote_loopback_get
 *
 * rloop     0x8000: bit 6
 * rloop     0x8300: bit 10
 */
int viper_remote_loopback_get (const PHYMOD_ST *pa, viper_actual_speed_id_t speed_id, uint32_t *lpbk)
{
    DIG_CTL1000X1r_t  x1reg;
    XGXSCTLr_t        xctrl;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    if (speed_id == VIPER_SPD_10G_CX4){
        XGXSCTLr_CLR(xctrl);
        READ_XGXSCTLr(&pa_copy, &xctrl);
        *lpbk = XGXSCTLr_RLOOPf_GET(xctrl);
    } else {
        DIG_CTL1000X1r_CLR (x1reg);
        READ_DIG_CTL1000X1r(pa, &x1reg);
        *lpbk = DIG_CTL1000X1r_REMOTE_LOOPBACKf_GET(x1reg);
    }
    return PHYMOD_E_NONE;
}

/*
 * viper_gloop10g_set
 *
 * Enable Gloop10G    0x1800_0000: 0x6040 
 *
 */
int viper_gloop10g_set (const PHYMOD_ST *pa, uint8_t enable)
{

    DEV3_PCS_CTL1r_t     ctl1;
    TX_AFE_ANATXMDATA1r_t  data1;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    READ_DEV3_PCS_CTL1r(pa, &ctl1);
    READ_TX_AFE_ANATXMDATA1r(&pa_copy, &data1);
    if (enable){
        DEV3_PCS_CTL1r_GLOOP10Gf_SET(ctl1, 0x1);    
        TX_AFE_ANATXMDATA1r_TX_ELECIDLEf_SET(data1, 0x1);
    } else {
        DEV3_PCS_CTL1r_GLOOP10Gf_SET(ctl1, 0x0);     
        TX_AFE_ANATXMDATA1r_TX_ELECIDLEf_SET(data1, 0x0);
    }
    WRITE_DEV3_PCS_CTL1r(pa, ctl1);
    WRITE_TX_AFE_ANATXMDATA1r(&pa_copy, data1);

    return PHYMOD_E_NONE;
}

/*
 * viper_gloop10g_get
 *
 * Get Gloop10G    0x1800_0000: 0x6040 
 *
 */
int viper_gloop10g_get (const PHYMOD_ST *pa, uint32_t *lpbk)
{

    DEV3_PCS_CTL1r_t     ctl1;
    
    DEV3_PCS_CTL1r_CLR(ctl1);
    READ_DEV3_PCS_CTL1r(pa, &ctl1);

    *lpbk = DEV3_PCS_CTL1r_GLOOP10Gf_GET(ctl1);     

    return PHYMOD_E_NONE;
}

/*
 * viper_100FX_global_loopback_ena
 *
 * Enable 100FX Gloop     0x0000: bit[14]
 *
 */
int viper_100FX_global_loopback_set (const PHYMOD_ST *pa, uint8_t enable)
{

    MIICTLr_t         miictl;

    MIICTLr_CLR(miictl);
    READ_MIICTLr(pa, &miictl);
    MIICTLr_GLOOPBACKf_SET(miictl, enable);
    PHYMOD_IF_ERR_RETURN(WRITE_MIICTLr(pa, miictl));

    return PHYMOD_E_NONE;
}

/*
 * viper_100FX_global_loopback_get
 *
 * Gloop     0x0000: bit[14]
 */
int viper_100FX_global_loopback_get (const PHYMOD_ST *pa, uint32_t *lpbk)
{
    MIICTLr_t         miictl;

    MIICTLr_CLR(miictl);
    PHYMOD_IF_ERR_RETURN(READ_MIICTLr(pa, &miictl));
    *lpbk = MIICTLr_GLOOPBACKf_GET(miictl);

    return PHYMOD_E_NONE;
}


/* 
 * viper_tx_lane_swap 
 *
 * Lane Swap 0x8169: Value
 *
 */
int viper_tx_lane_swap (PHYMOD_ST *pa,  uint32_t  lane_map)
{
    TXLNSWP1r_t  ln_swap;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;


    /* Clear Registers */
    TXLNSWP1r_CLR(ln_swap);

    TXLNSWP1r_TX0_LNSWAP_SELf_SET(ln_swap, (lane_map & 0x3));
    TXLNSWP1r_TX1_LNSWAP_SELf_SET(ln_swap, (lane_map >> 4) & 0x3);
    TXLNSWP1r_TX2_LNSWAP_SELf_SET(ln_swap, (lane_map >> 8) & 0x3);
    TXLNSWP1r_TX3_LNSWAP_SELf_SET(ln_swap, (lane_map >> 12) & 0x3);

    PHYMOD_IF_ERR_RETURN(MODIFY_TXLNSWP1r(&pa_copy, ln_swap));

    return PHYMOD_E_NONE;
}

/* 
 * viper_rx_lane_swap 
 *
 * Lane Swap 0x816b: Value
 *
 */
int viper_rx_lane_swap (PHYMOD_ST *pa, uint32_t lane_map)
{
    RXLNSWP1r_t  ln_swap;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    /* Clear Registers */
    RXLNSWP1r_CLR(ln_swap);

    RXLNSWP1r_RX0_LNSWAP_SELf_SET(ln_swap, (lane_map & 0x3));
    RXLNSWP1r_RX1_LNSWAP_SELf_SET(ln_swap, (lane_map >> 4) & 0x3);
    RXLNSWP1r_RX2_LNSWAP_SELf_SET(ln_swap, (lane_map >> 8) & 0x3);
    RXLNSWP1r_RX3_LNSWAP_SELf_SET(ln_swap, (lane_map >> 12) & 0x3);

    PHYMOD_IF_ERR_RETURN(MODIFY_RXLNSWP1r(&pa_copy, ln_swap));

    return PHYMOD_E_NONE;
}

/* 
 * viper_tx_lane_swap_get 
 *
 * Lane Swap 0x8169: Value Get 
 *
 */
int viper_tx_lane_swap_get (const PHYMOD_ST *pc, uint32_t *tx_lane_map)
{
 
    uint16_t tx_lane_map_0 = 0; 
    uint16_t tx_lane_map_1 = 0; 
    uint16_t tx_lane_map_2 = 0;
    uint16_t tx_lane_map_3 = 0;
    TXLNSWP1r_t  ln_swap;

    READ_TXLNSWP1r(pc, &ln_swap);
    tx_lane_map_0 = TXLNSWP1r_TX0_LNSWAP_SELf_GET(ln_swap);
    tx_lane_map_1 = TXLNSWP1r_TX1_LNSWAP_SELf_GET(ln_swap);
    tx_lane_map_2 = TXLNSWP1r_TX2_LNSWAP_SELf_GET(ln_swap);
    tx_lane_map_3 = TXLNSWP1r_TX3_LNSWAP_SELf_GET(ln_swap);

    *tx_lane_map = ((tx_lane_map_0 & 0x3) << 0)
                 | ((tx_lane_map_1 & 0x3) << 4)
                 | ((tx_lane_map_2 & 0x3) << 8)
                 | ((tx_lane_map_3 & 0x3) << 12);

    return PHYMOD_E_NONE ;
}

/*
 * viper_rx_lane_swap_get
 *
 * Lane Swap 0x816B: Value Get
 *
 */
int viper_rx_lane_swap_get (const PHYMOD_ST *pc, uint32_t *rx_lane_map)
{

    uint16_t rx_lane_map_0 = 0;
    uint16_t rx_lane_map_1 = 0; 
    uint16_t rx_lane_map_2 = 0; 
    uint16_t rx_lane_map_3 = 0;
    RXLNSWP1r_t ln_swap;

    READ_RXLNSWP1r(pc, &ln_swap);
    rx_lane_map_0 = RXLNSWP1r_RX0_LNSWAP_SELf_GET(ln_swap);
    rx_lane_map_1 = RXLNSWP1r_RX1_LNSWAP_SELf_GET(ln_swap);
    rx_lane_map_2 = RXLNSWP1r_RX2_LNSWAP_SELf_GET(ln_swap);
    rx_lane_map_3 = RXLNSWP1r_RX3_LNSWAP_SELf_GET(ln_swap);

    *rx_lane_map = ((rx_lane_map_0 & 0x3) << 0)
                 | ((rx_lane_map_1 & 0x3) << 4)
                 | ((rx_lane_map_2 & 0x3) << 8)
                 | ((rx_lane_map_3 & 0x3) << 12);

    return PHYMOD_E_NONE ;
}


/* 
 * viper_tx_pol_set 
 *
 * Polarity Flip 0x8061: 0x0020
 *
 */
int viper_tx_pol_set (const PHYMOD_ST *pa, uint8_t val)
{

    TX_AFE_ANATXACTL0r_t  reg;

    READ_TX_AFE_ANATXACTL0r(pa, &reg);
    TX_AFE_ANATXACTL0r_TXPOL_FLIPf_SET(reg, val);
    WRITE_TX_AFE_ANATXACTL0r(pa, reg);

    return PHYMOD_E_NONE;
}


/* 
 * viper_rx_pol_set 
 *
 * Polarity Flip 0x80ba: 0x001c
 *
 */
int viper_rx_pol_set (const PHYMOD_ST *pa, uint8_t val)
{

    RX_AFE_ANARXCTLPCIr_t  reg;

    RX_AFE_ANARXCTLPCIr_CLR(reg);
    READ_RX_AFE_ANARXCTLPCIr(pa, &reg);
    /*RX_AFE_ANARXCTLPCIr_LINK_EN_Rf_SET(reg, val);*/
    
    RX_AFE_ANARXCTLPCIr_LINK_EN_Rf_SET(reg, 1);
    RX_AFE_ANARXCTLPCIr_RX_POLARITY_FORCE_SMf_SET(reg, val);
    RX_AFE_ANARXCTLPCIr_RX_POLARITY_Rf_SET(reg, val);

    WRITE_RX_AFE_ANARXCTLPCIr(pa, reg);

    return PHYMOD_E_NONE;
}

/*
 * viper_pol_get
 */
int viper_tx_pol_get (const PHYMOD_ST *pa, uint32_t *val)
{
    TX_AFE_ANATXACTL0r_t  reg;


    READ_TX_AFE_ANATXACTL0r(pa, &reg);
    *val = TX_AFE_ANATXACTL0r_TXPOL_FLIPf_GET(reg);

    return PHYMOD_E_NONE;
}


/*
 * viper_rx_pol_get 
 */
int viper_rx_pol_get (const PHYMOD_ST *pa, uint32_t *val)
{
    RX_AFE_ANARXCTLPCIr_t  reg;

    READ_RX_AFE_ANARXCTLPCIr(pa, &reg);
    *val = RX_AFE_ANARXCTLPCIr_RX_POLARITY_Rf_GET(reg);

    return PHYMOD_E_NONE;
}


/* 
 * viper_pll_lock_speed_up 
 *
 * Calib Charge Time 0x8183 : 0x002A 
 * Calib Delay  Time 0x8184 : 0x021C 
 * Calib Step   Time 0x8185 : 0x0055 
 *
 */
int viper_pll_lock_speed_up (PHYMOD_ST *pa)
{
    PLL2_CTL3r_t   ctrl3;
    PLL2_CTL4r_t   ctrl4;
    PLL2_CTL5r_t   ctrl5;

    PLL2_CTL3r_SET(ctrl3, 0x002A);
    PLL2_CTL4r_SET(ctrl4, 0x021C);
    PLL2_CTL5r_SET(ctrl5, 0x0055);

    MODIFY_PLL2_CTL3r(pa, ctrl3);
    MODIFY_PLL2_CTL4r(pa, ctrl4);
    MODIFY_PLL2_CTL5r(pa, ctrl5);

    return PHYMOD_E_NONE;
}


/* 
 * viper_an_speed_up 
 *
 * enable fast timers 0x8301 : 0x0040 
 *
 */
int viper_an_speed_up (PHYMOD_ST *pa)
{
    DIG_CTL1000X2r_t   ctrl;

    READ_DIG_CTL1000X2r (pa, &ctrl);
    DIG_CTL1000X2r_AUTONEG_FAST_TIMERSf_SET(ctrl, 1);
    MODIFY_DIG_CTL1000X2r (pa, ctrl);

    return PHYMOD_E_NONE;
}


/* 
 * viper_forced_speed_up 
 *
 * clock speed up   0x8309 : 0x2790 
 * fx100 fast timer 0x8402 : 0x0801 
 *
 */
int viper_forced_speed_up (PHYMOD_ST *pa)
{
    DIG_MISC2r_t      misc2;
    FX100_CTL3r_t     ctrl3;

    DIG_MISC2r_CLR(misc2);
    DIG_MISC2r_RESERVED_14_13f_SET(misc2, 1);
    DIG_MISC2r_CLKSIGDET_BYPASSf_SET(misc2, 1);
    DIG_MISC2r_CLK41_BYPASSf_SET(misc2, 1);
    DIG_MISC2r_MIIGMIIDLY_ENf_SET(misc2, 1);
    DIG_MISC2r_MIIGMIIMUX_ENf_SET(misc2, 1);
    DIG_MISC2r_FIFO_ERR_CYAf_SET(misc2, 1);
    MODIFY_DIG_MISC2r(pa, misc2);

    FX100_CTL3r_CLR(ctrl3);
    FX100_CTL3r_NUMBER_OF_IDLEf_SET(ctrl3, 8);
    FX100_CTL3r_FAST_TIMERSf_SET(ctrl3, 1);
    MODIFY_FX100_CTL3r(pa, ctrl3);

    return PHYMOD_E_NONE;
}


/* 
 * viper_prbs_generator
 *
 * Disable CL36      0x8015 : 0x0000 
 * Set 1G Mode       0x8016 : 0x0000 
 * Disable cden/eden 0x8017 : 0x0000 
 * set prbs order    0x8019 : 0x3333 
 * enable prbs       0x8019 : 0xBBBB 
 * choose tx datai   0x815A : 0x00F0 
 * Broadcast         0xFFDE : 0x001F 
 * OS2/0s5           0x834A : 0x000X
 *
 */
int viper_prbs_generator (PHYMOD_ST *pa, uint8_t os_mode)
{
    LANECTL0r_t      lane_ctl0;
    LANECTL1r_t      lane_ctl1;
    LANECTL2r_t      lane_ctl2;
    PRBS_DECOUPLEr_t  prbs_reg;
    AERr_t           aereg;
    DIG_MISC8r_t      misc8;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    PRBS_DECOUPLEr_CLR(prbs_reg);
    AERr_CLR(aereg);
    DIG_MISC8r_CLR(misc8);

    /* Disable CL36 */
    LANECTL0r_CLR(lane_ctl0);
    WRITE_LANECTL0r(pa, lane_ctl0);

    /* Set 1G mode */
    LANECTL1r_CLR(lane_ctl1);
    WRITE_LANECTL1r(&pa_copy, lane_ctl1);

    /* Disable cden/eden */
    LANECTL2r_CLR(lane_ctl2);
    WRITE_LANECTL2r(&pa_copy, lane_ctl2);
    
    /* Choose tx_datai*/
    PRBS_DECOUPLEr_TX_DATAI_PRBS_SEL_0f_SET(prbs_reg, 1);
    PRBS_DECOUPLEr_TX_DATAI_PRBS_SEL_1f_SET(prbs_reg, 1);
    PRBS_DECOUPLEr_TX_DATAI_PRBS_SEL_2f_SET(prbs_reg, 1);
    PRBS_DECOUPLEr_TX_DATAI_PRBS_SEL_3f_SET(prbs_reg, 1);
    WRITE_PRBS_DECOUPLEr(&pa_copy, prbs_reg);
    
    /* Broadcast */   
    AERr_MMD_PORTf_SET(aereg, 0x1ff);
    MODIFY_AERr(&pa_copy, aereg);

    /* Set os2/os5 mode */
    DIG_MISC8r_FORCE_OSCDR_MODEf_SET(misc8, os_mode);
    MODIFY_DIG_MISC8r(pa, misc8);

    return PHYMOD_E_NONE;
}


/**
@brief   Read Link status
@param   pc handle to current VIPER context (#PHYMOD_ST)
@param   *link Reference for Status of PCS Link
@returns The value PHYMOD_E_NONE upon successful completion
@details Return the status of the PCS link. The link up implies the PCS is able
to decode the digital bits coming in on the serdes. It automatically implies
that the PLL is stable and that the PMD sublayer has successfully recovered the
clock on the receive line.
*/
int viper_get_link_status(const PHYMOD_ST* pc, uint32_t *link)
{
    DIG_STS1000X1r_t sts;
    DIG_STS1000X1r_CLR(sts);

    PHYMOD_IF_ERR_RETURN(READ_DIG_STS1000X1r(pc, &sts));
    *link = DIG_STS1000X1r_LINK_STATUSf_GET(sts);

    return PHYMOD_E_NONE;
}

int viper_get_link_status_10G(const PHYMOD_ST* pc, uint32_t *link)
{
    XGXSSTS1r_t reg; 
    XGXSSTS1r_CLR(reg);

    PHYMOD_IF_ERR_RETURN(READ_XGXSSTS1r(pc, &reg));
    *link = XGXSSTS1r_LINKSTATf_GET(reg); 

    return PHYMOD_E_NONE;

}


/**
@brief   This function reads TX-PMD PMD_LOCK bit.
@param   pc handle to current TSCE context (#PHYMOD_ST)
@param   lockStatus reference which is updated with pmd_lock status
@returns PHYMOD_E_NONE if no errors. PHYMOD_E_FAIL else.
@details Read PMD lock status Returns 1 or 0 (locked/not)
*/

int viper_pmd_lock_get(const PHYMOD_ST* pc, uint32_t* lockStatus)
{
    /* Place Holder */
    return PHYMOD_E_NONE;
}

int viper_autoneg_status_get(const PHYMOD_ST *pc, phymod_autoneg_status_t *status)
{

    /* Place Holder */
    /*
     * status->enabled   = 
     * status->locked    = 
     * status->data_rate = 
     * status->interface = phymodInterfaceXFI;
     */ 
    return PHYMOD_E_NONE;
}

int viper_autoneg_get(const PHYMOD_ST *pc, phymod_autoneg_control_t  *an, 
                      uint32_t                  *an_done)
{
    MIICTLr_t   miictl;
    MIISTATr_t  miistat;

    READ_MIICTLr(pc, &miictl);
    READ_MIISTATr(pc, &miistat);

    an->enable = MIICTLr_AUTONEG_ENABLEf_GET(miictl);
    *an_done   = MIISTATr_AUTONEG_COMPLETEf_GET(miistat);

    return PHYMOD_E_NONE;
}

int viper_autoneg_set(const PHYMOD_ST* pa, const phymod_autoneg_control_t* an)
{
    MIICTLr_t         miictl;
    DIG_CTL1000X1r_t  x1reg;
    DIG_CTL1000X2r_t  x2reg;

    if (an->enable){
        if (an->an_mode == phymod_AN_MODE_CL37){
            PHYMOD_IF_ERR_RETURN(viper_fiber_AN_1G(pa));
        } else {
            PHYMOD_IF_ERR_RETURN(viper_sgmii_slave_aneg_speed(pa));
        }
        /* Enable auto detection */
        READ_DIG_CTL1000X1r(pa, &x1reg);
        DIG_CTL1000X1r_AUTODET_ENf_SET(x1reg, 1);
        WRITE_DIG_CTL1000X1r(pa, x1reg);

        /* Enable parallel detection */
        READ_DIG_CTL1000X2r(pa, &x2reg);
        DIG_CTL1000X2r_ENABLE_PARALLEL_DETECTIONf_SET(x2reg, 1);
        WRITE_DIG_CTL1000X2r(pa, x2reg);
    } else {
        READ_MIICTLr(pa, &miictl);
        MIICTLr_AUTONEG_ENABLEf_SET(miictl, 0);
        WRITE_MIICTLr(pa, miictl);

        /* Disable auto detection */
        READ_DIG_CTL1000X1r(pa, &x1reg);
        DIG_CTL1000X1r_AUTODET_ENf_SET(x1reg, 0);
        WRITE_DIG_CTL1000X1r(pa, x1reg);
   }

    return PHYMOD_E_NONE;
}
 
static int _viper_getRevDetails(const PHYMOD_ST* pc)
{
    SERDESID0r_t reg_serdesid;

    SERDESID0r_CLR(reg_serdesid);
    PHYMOD_IF_ERR_RETURN(READ_SERDESID0r(pc,&reg_serdesid));
    return (SERDESID0r_GET(reg_serdesid));
}


/**
@brief   Read the 16 bit rev. id value etc.
@param   pc handle to current VIPER context (#PHYMOD_ST)
@param   *revid int ref. to return revision id to calling function.
@returns The value PHYMOD_E_NONE upon successful completion.
@details
This  fucntion reads the revid register that contains core number, revision
number and returns the 16-bit value in the revid
*/
int viper_revid_read(const PHYMOD_ST* pc, uint32_t *revid)              /* REVID_READ */
{
    *revid=_viper_getRevDetails(pc);
    /* VIPER_DBG_IN_FUNC_VOUT_INFO(pc,("revid: %x", *revid)); */
    return PHYMOD_E_NONE;
}

int viper_tsc_tx_pi_freq_override (const PHYMOD_ST *pa, 
                                   uint8_t                enable, 
                                   int16_t                freq_override_val) 
{
#if 0
/* HEADER FILE SHOULD BE FIXED 806A - 806E */
   if (enable) {
     wrc_tx_pi_en(0x1);                                 /* TX_PI enable :            0 = disabled, 1 = enabled */
     wrc_tx_pi_freq_override_en(0x1);                   /* Fixed freq mode enable:   0 = disabled, 1 = enabled */
     wrc_tx_pi_freq_override_val(freq_override_val);    /* Fixed Freq Override Value (+/-8192) */
   }
   else {
     wrc_tx_pi_freq_override_val(0);                    /* Fixed Freq Override Value to 0 */
     wrc_tx_pi_freq_override_en(0x0);                   /* Fixed freq mode enable:   0 = disabled, 1 = enabled */
     wrc_tx_pi_en(0x0);                                 /* TX_PI enable :            0 = disabled, 1 = enabled */
   }
#endif
  return (PHYMOD_E_NONE);
}

/*
 * 
 *
*/
int viper_reg_set_wait_check(PHYMOD_ST *pc, int bit_num, int bitset, int timeout)
{

  return (PHYMOD_E_NONE);
}


int viper_pll_lock_wait(PHYMOD_ST *pc)
{
#if 0
    int rv;
    
    rv = viper_regbit_set_wait_check(pc, 0x8001,
                   0x100, 1, 20000);

    if (rv == PHYMOD_E_TIMEOUT) {
        printf("%-22s: Error. Timeout TXPLL lock: port %d \n", FUNCTION_NAME(), pc->port);
        return (PHYMOD_E_TIMEOUT);
    }
#endif
    return PHYMOD_E_NONE;
}

int viper_tx_afe_post_set(const PHYMOD_ST *pc, uint8_t enable, uint8_t post)
{
    TX_AFE_CTL1r_t tx_reg;

    READ_TX_AFE_CTL1r(pc, &tx_reg);
    TX_AFE_CTL1r_POST_ENABLEf_SET(tx_reg, 1);
    TX_AFE_CTL1r_POST_CONTROLf_SET(tx_reg, post);
    MODIFY_TX_AFE_CTL1r(pc, tx_reg);

    return (PHYMOD_E_NONE);
}

int viper_pll_sequencer_control(const PHYMOD_ST *pc, int enable)
{
    if (enable) {
        /* Enable PLL sequencer */
          /*viper_pll_enable(pc);*/
        /*May need to wait */
        /*viper_pll_lock_wait(pc); */
    } else {
        /* Reset PLL sequencer */
        /*viper_pll_disable(pc);*/
    }

    return (PHYMOD_E_NONE);
}

int viper_sgmii_mode_get (const PHYMOD_ST *pa, uint16_t *sgmii_mode)
{
    DIG_STS1000X1r_t sreg;

    READ_DIG_STS1000X1r(pa, &sreg);
    *sgmii_mode = DIG_STS1000X1r_SGMII_MODEf_GET(sreg);

    return (PHYMOD_E_NONE);
}


#if 0
int viper_lane_power_set(PHYMOD_ST *pa, uint16_t data, uint16_t mask)
{
    LANECTL3r_t reg;
    
    READ_LANECTL3r(pa, &reg);  
    LANECTL3r_PWRDWN_FORCEf_SET(reg, (data & 0x800) >> 8); 
    LANECTL3r_PWRDN_RXf_SET(reg, (data >> 4) & 0xf);
    LANECTL3r_PWRDN_TXf_SET(reg, (data & 0xf));
    MODIFY_LANECTL3r(pa, reg);  

    return (PHYMOD_E_NONE);
}
#endif

int viper_xgxs_sel(const PHYMOD_ST *pa, int xgxs_select)
{
    PLL_AFE_TCATIMER1r_t treg;

    READ_PLL_AFE_TCATIMER1r(pa, &treg);
    if (xgxs_select){
        PLL_AFE_TCATIMER1r_XGXS_SELf_SET(treg, 0x1); 
    } else {
        PLL_AFE_TCATIMER1r_XGXS_SELf_SET(treg, 0x0); 
    }
    WRITE_PLL_AFE_TCATIMER1r(pa, treg);


    return (PHYMOD_E_NONE);
}


int viper_set_spd_intf(PHYMOD_ST *pa, viper_spd_intfc_type_t type)
{
    viper_speed_ctrl_reset(pa);
    switch(type){
        case VIPER_SPD_10_SGMII:
        case VIPER_SPD_100_SGMII:
        case VIPER_SPD_1000_SGMII:
            PHYMOD_IF_ERR_RETURN(viper_sgmii_force_speed(pa, (uint8_t)type));
            break; 
        case VIPER_SPD_100_FX:
            PHYMOD_IF_ERR_RETURN(viper_fiber_force_100FX(pa));
            break; 
        case VIPER_SPD_1000_X1:
            PHYMOD_IF_ERR_RETURN(viper_fiber_force_1G(pa));
            break; 
        case VIPER_SPD_2500:
            PHYMOD_IF_ERR_RETURN(viper_fiber_force_2p5G(pa));
            break; 
        case VIPER_SPD_10000:
            /*PHYMOD_IF_ERR_RETURN(viper_fiber_force_speed(pa, VIPER_MISC1_10GHiGig_X4));*/
            PHYMOD_IF_ERR_RETURN(viper_fiber_force_speed(pa, VIPER_MISC1_10GBASE_CX4));
            break; 
        case VIPER_SPD_10000_CX4:
            PHYMOD_IF_ERR_RETURN(viper_xgxs_sel(pa, 1));
            PHYMOD_IF_ERR_RETURN(viper_fiber_force_speed(pa, VIPER_MISC1_10GBASE_CX4));
            break; 
        default:
            PHYMOD_IF_ERR_RETURN(viper_fiber_force_1G(pa));
            break; 
    }
    return (PHYMOD_E_NONE);
}

int viper_actual_speed_get(const PHYMOD_ST* pa, viper_actual_speed_id_t *speed_id)
{
    XGXSSTS1r_t xreg;  
    DIG_STS1000X1r_t sreg; 

    if (pa->lane_mask == 0xf) {
        READ_XGXSSTS1r(pa, &xreg);
        *speed_id = XGXSSTS1r_ACTUAL_SPEED_LN0f_GET(xreg);
    } else {
        READ_DIG_STS1000X1r(pa, &sreg);
        *speed_id = DIG_STS1000X1r_SPEED_STATUSf_GET(sreg);
    }
    return PHYMOD_E_NONE;
}

int viper_speed_id_interface_config_get(const phymod_phy_access_t* phy, int speed_id, phymod_phy_inf_config_t* config)
{
    uint16_t sgmii_mode = 0;
    switch (speed_id) {
        case VIPER_SPD_10M:
            config->data_rate = 10;
            config->interface_type = phymodInterfaceSGMII;
            break;
        case VIPER_SPD_100M:
            config->data_rate = 100;
            PHYMOD_IF_ERR_RETURN(viper_sgmii_mode_get(&phy->access, &sgmii_mode));
            if (sgmii_mode){
                config->interface_type = phymodInterfaceSGMII;
            } else {
                config->interface_type = phymodInterface1000X;
            }
            break;
        case VIPER_SPD_1G:
            config->data_rate = 1000;
            PHYMOD_IF_ERR_RETURN(viper_sgmii_mode_get(&phy->access, &sgmii_mode));
            if (sgmii_mode){
                config->interface_type = phymodInterfaceSGMII;
            } else { 
                config->interface_type = phymodInterface1000X;
            }
            break;
        case VIPER_SPD_2p5G:
            config->data_rate = 2500;
            config->interface_type = phymodInterface1000X;
            break;
        case VIPER_SPD_10G_HiG:
        case VIPER_SPD_10G_CX4:
            config->data_rate = 10000;
            config->interface_type = phymodInterfaceXGMII;
            break;
        default: 
            config->data_rate = 10;
            config->interface_type = phymodInterfaceSGMII;
            break;
    }

    return PHYMOD_E_NONE;
}

int viper_phy_enable_set(const PHYMOD_ST *pa, int enable, int combo)
{
    LANECTL3r_t ctl3;
    DIG_MISC3r_t misc3;
    LANERESETr_t rst;
    uint8_t lane_ena;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;
    DIG_MISC3r_CLR(misc3);

    if (enable) {
        READ_LANECTL3r(&pa_copy, &ctl3);
        READ_LANERESETr(&pa_copy, &rst);

        lane_ena = (~(pa->lane_mask)) & LANECTL3r_PWRDN_RXf_GET(ctl3);
        LANECTL3r_PWRDN_RXf_SET(ctl3, lane_ena);
        LANERESETr_RESET_RXf_SET(rst, lane_ena);

        lane_ena = (~(pa->lane_mask)) & LANECTL3r_PWRDN_TXf_GET(ctl3);
        LANECTL3r_PWRDN_TXf_SET(ctl3, lane_ena);
        LANERESETr_RESET_TXf_SET(rst, lane_ena);

        PHYMOD_IF_ERR_RETURN(WRITE_LANECTL3r(&pa_copy, ctl3));
        PHYMOD_IF_ERR_RETURN(WRITE_LANERESETr(&pa_copy,rst));

        DIG_MISC3r_LANEDISABLEf_SET(misc3, 0);
        PHYMOD_IF_ERR_RETURN(WRITE_DIG_MISC3r(pa, misc3));


    } else {
        READ_LANECTL3r(&pa_copy, &ctl3);
        READ_LANERESETr(&pa_copy, &rst);

        lane_ena = (pa->lane_mask) | LANECTL3r_PWRDN_RXf_GET(ctl3);
        LANECTL3r_PWRDN_RXf_SET(ctl3, lane_ena);
        LANERESETr_RESET_RXf_SET(rst, lane_ena);

        lane_ena = (pa->lane_mask) | LANECTL3r_PWRDN_TXf_GET(ctl3);
        LANECTL3r_PWRDN_TXf_SET(ctl3, lane_ena);
        LANERESETr_RESET_TXf_SET(rst, lane_ena);

        PHYMOD_IF_ERR_RETURN(WRITE_LANECTL3r(&pa_copy, ctl3));
        PHYMOD_IF_ERR_RETURN(WRITE_LANERESETr(&pa_copy,rst));

        DIG_MISC3r_LANEDISABLEf_SET(misc3, 1);
        PHYMOD_IF_ERR_RETURN(WRITE_DIG_MISC3r(pa, misc3));
    }
    if (combo){
        MISCCTL1r_t mctrl;
        RX_AFE_ANARXCTLr_t rxctrl;

        READ_MISCCTL1r(&pa_copy, &mctrl);
        MISCCTL1r_GLOBAL_PMD_TX_DISABLEf_SET(mctrl, ~enable);
        PHYMOD_IF_ERR_RETURN(WRITE_MISCCTL1r(&pa_copy, mctrl));

        READ_RX_AFE_ANARXCTLr(&pa_copy, &rxctrl);
        RX_AFE_ANARXCTLr_OVERRIDE_SIGDET_ENf_SET(rxctrl, ~enable);
        PHYMOD_IF_ERR_RETURN(MODIFY_RX_AFE_ANARXCTLr(&pa_copy, rxctrl));
    }

    return PHYMOD_E_NONE;
}

int viper_phy_enable_get(const PHYMOD_ST *pa, int *enable )
{
    LANECTL3r_t ctl3;
    int tx_value = 0;
    int rx_value = 0;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    READ_LANECTL3r(&pa_copy, &ctl3);
    rx_value = pa->lane_mask & LANECTL3r_PWRDN_RXf_GET(ctl3);
    tx_value = pa->lane_mask & LANECTL3r_PWRDN_TXf_GET(ctl3);

    if (tx_value | rx_value){
        *enable = 0;
    } else {
        *enable = 1;
    }

    return PHYMOD_E_NONE;
}


/*
 * viper_speed_ctrl_reset
 *
 *  Reset 0xffe0 
 *  Reset 0x8308 
 *
 */
int viper_speed_ctrl_reset(PHYMOD_ST *pa)
{
    MIICTLr_t         miictl;
    DIG_MISC1r_t      misc1;
    FX100_CTL1r_t     xctl1;
    FX100_CTL2r_t     xctl2;
    FX100_CTL3r_t     xctl3;
    DIG_CTL1000X1r_t  x1reg;
    uint32_t lpbk = 0;

    MIICTLr_CLR(miictl);
    DIG_MISC1r_CLR(misc1);
    FX100_CTL1r_CLR(xctl1);
    FX100_CTL2r_CLR(xctl2);
    FX100_CTL3r_CLR(xctl3);
    DIG_CTL1000X1r_CLR(x1reg);

    PHYMOD_IF_ERR_RETURN(viper_100FX_global_loopback_get(pa, &lpbk));
    if (!lpbk){
        MIICTLr_SET(miictl, 0x140);
        PHYMOD_IF_ERR_RETURN(WRITE_MIICTLr(pa, miictl));
    }

    DIG_MISC1r_SET(misc1, 0xc000);
    PHYMOD_IF_ERR_RETURN(WRITE_DIG_MISC1r(pa, misc1));

    FX100_CTL1r_SET(xctl1, 0x14a);
    PHYMOD_IF_ERR_RETURN(WRITE_FX100_CTL1r(pa, xctl1));

    FX100_CTL2r_SET(xctl2, 0x0);
    PHYMOD_IF_ERR_RETURN(WRITE_FX100_CTL2r(pa, xctl2));

    FX100_CTL3r_SET(xctl3, 0x800);
    PHYMOD_IF_ERR_RETURN(WRITE_FX100_CTL3r(pa, xctl3));

    /*DIG_CTL1000X1r_SET(x1reg, 0x101);*/
    DIG_CTL1000X1r_FIBER_MODE_1000Xf_SET(x1reg, 1);
    DIG_CTL1000X1r_COMMA_DET_ENf_SET(x1reg, 1);
    PHYMOD_IF_ERR_RETURN(MODIFY_DIG_CTL1000X1r(pa, x1reg));

    return PHYMOD_E_NONE;
    
}

int viper_multimmds_set(PHYMOD_ST *pa, int enable)
{
    MMDSELr_t mreg;

    READ_MMDSELr(pa, &mreg);
    MMDSELr_MULTIMMDS_ENf_SET(mreg, enable);

    PHYMOD_IF_ERR_RETURN(WRITE_MMDSELr(pa, mreg));

    return PHYMOD_E_NONE;
   
}

int viper_autoneg_local_ability_set(const PHYMOD_ST *pa, viper_an_adv_ability_t *ability)
{
    COMBO_AUTONEGADVr_t areg;

    READ_COMBO_AUTONEGADVr(pa, &areg);
    COMBO_AUTONEGADVr_PAUSEf_SET(areg, ability->an_pause);
    PHYMOD_IF_ERR_RETURN(WRITE_COMBO_AUTONEGADVr(pa, areg));;

    return PHYMOD_E_NONE;
}

int viper_autoneg_local_ability_get(const PHYMOD_ST *pa, viper_an_adv_ability_t *ability)
{
    COMBO_AUTONEGADVr_t areg;
    DIG_STS1000X1r_t sreg;

    READ_COMBO_AUTONEGADVr(pa, &areg);
    ability->an_pause = COMBO_AUTONEGADVr_PAUSEf_GET(areg);

    READ_DIG_STS1000X1r(pa, &sreg);
    ability->cl37_sgmii_speed = DIG_STS1000X1r_SPEED_STATUSf_GET(sreg);

    return PHYMOD_E_NONE;
}

int viper_autoneg_remote_ability_get(const PHYMOD_ST *pa, viper_an_adv_ability_t *ability)
{
    COMBO_AUTONEGLPABILr_t areg;
    int sgmii_mode;

    READ_COMBO_AUTONEGLPABILr(pa, &areg);
    ability->an_pause = COMBO_AUTONEGLPABILr_PAUSEf_GET(areg);
    sgmii_mode = COMBO_AUTONEGLPABILr_SGMII_MODEf_GET(areg);

    if (sgmii_mode){
        ability->cl37_sgmii_speed = ((((areg).combo_autoneglpabil[0]) >> 10) & 0x3);
    }

    return PHYMOD_E_NONE;
}

/*
 * viper_10G_CX4_compliance
 *
 * tx_rate select   0x8069 : bit[7] = 0
 * rx_pf_ctrl       0x80b4 : bit[15:12] = 0xe
 *
 */
int viper_10G_CX4_compliance_set(const PHYMOD_ST *pa, uint16_t value)
{
    TX_AFE_INTERPr_t         txreg;
    RX_AFE_ANARXSIGDETr_t    rxreg;
    phymod_access_t pa_copy;

    PHYMOD_MEMCPY(&pa_copy, pa, sizeof(pa_copy));
    pa_copy.lane_mask = 0x1;

    READ_TX_AFE_INTERPr(&pa_copy, &txreg);
    TX_AFE_INTERPr_TX_RATESELECTf_SET(txreg, 1);
    PHYMOD_IF_ERR_RETURN(WRITE_TX_AFE_INTERPr(&pa_copy, txreg));

    READ_RX_AFE_ANARXSIGDETr(&pa_copy, &rxreg);
    RX_AFE_ANARXSIGDETr_RX_PF_CTRLf_SET(rxreg, value & 0xf);
    PHYMOD_IF_ERR_RETURN(WRITE_RX_AFE_ANARXSIGDETr(&pa_copy, rxreg));

    return PHYMOD_E_NONE;
}
/* 
 * viper_rx_los_set
 *
 * enable hw rx los    0x8300: 0x04
 *
 */
int viper_signal_detect_set (PHYMOD_ST *pa)
{
    DIG_CTL1000X1r_t  x1reg;

    /* Clear Registers */
    DIG_CTL1000X1r_CLR(x1reg);

    /* Bit 2 enable signal detetct */
    DIG_CTL1000X1r_SIGNAL_DETECT_ENf_SET(x1reg, 1);
    MODIFY_DIG_CTL1000X1r(pa, x1reg);

    return PHYMOD_E_NONE;
}

/*
 * viper_rx_los_invert_set
 *
 * invert signal detect  0x8300: 0x08
 *
 */
int viper_signal_invert_set (PHYMOD_ST *pa)
{
    DIG_CTL1000X1r_t  x1reg;

    /* Clear Registers */
    DIG_CTL1000X1r_CLR(x1reg);

    /* Bit 3 invert signal detetct */
    DIG_CTL1000X1r_INVERT_SIGNAL_DETECTf_SET(x1reg, 1);
    MODIFY_DIG_CTL1000X1r(pa, x1reg);

    return PHYMOD_E_NONE;
}

/*
 * viper_fiber_force_100FX_get
 *
 * Get FX Mode      0x8400: bit[0]
 *
 */
int viper_fiber_force_100FX_get (const PHYMOD_ST *pa, uint32_t *fx_mode)
{
    FX100_CTL1r_t     fxctrl;

    FX100_CTL1r_CLR(fxctrl);
    PHYMOD_IF_ERR_RETURN(READ_FX100_CTL1r(pa, &fxctrl));
    *fx_mode = FX100_CTL1r_ENABLEf_GET(fxctrl);

    return PHYMOD_E_NONE;
}
