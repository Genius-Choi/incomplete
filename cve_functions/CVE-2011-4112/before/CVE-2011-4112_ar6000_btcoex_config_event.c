ar6000_btcoex_config_event(struct ar6_softc *ar,  u8 *ptr, u32 len)
{

    WMI_BTCOEX_CONFIG_EVENT *pBtcoexConfig = (WMI_BTCOEX_CONFIG_EVENT *)ptr;
    WMI_BTCOEX_CONFIG_EVENT *pArbtcoexConfig =&ar->arBtcoexConfig;

    AR_DEBUG_PRINTF(ATH_DEBUG_INFO,("AR6000 BTCOEX CONFIG EVENT \n"));

    A_PRINTF("received config event\n");
    pArbtcoexConfig->btProfileType = pBtcoexConfig->btProfileType;
    pArbtcoexConfig->linkId = pBtcoexConfig->linkId;

    switch (pBtcoexConfig->btProfileType) {
        case WMI_BTCOEX_BT_PROFILE_SCO:
            memcpy(&pArbtcoexConfig->info.scoConfigCmd, &pBtcoexConfig->info.scoConfigCmd,
                                        sizeof(WMI_SET_BTCOEX_SCO_CONFIG_CMD));
            break;
        case WMI_BTCOEX_BT_PROFILE_A2DP:
            memcpy(&pArbtcoexConfig->info.a2dpConfigCmd, &pBtcoexConfig->info.a2dpConfigCmd,
                                        sizeof(WMI_SET_BTCOEX_A2DP_CONFIG_CMD));
            break;
        case WMI_BTCOEX_BT_PROFILE_ACLCOEX:
            memcpy(&pArbtcoexConfig->info.aclcoexConfig, &pBtcoexConfig->info.aclcoexConfig,
                                        sizeof(WMI_SET_BTCOEX_ACLCOEX_CONFIG_CMD));
            break;
        case WMI_BTCOEX_BT_PROFILE_INQUIRY_PAGE:
           memcpy(&pArbtcoexConfig->info.btinquiryPageConfigCmd, &pBtcoexConfig->info.btinquiryPageConfigCmd,
                                        sizeof(WMI_SET_BTCOEX_ACLCOEX_CONFIG_CMD));
            break;
    }
    if (ar->statsUpdatePending) {
         ar->statsUpdatePending = false;
          wake_up(&arEvent);
    }
}
