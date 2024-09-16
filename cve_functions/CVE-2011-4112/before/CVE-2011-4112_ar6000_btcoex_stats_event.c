ar6000_btcoex_stats_event(struct ar6_softc *ar,  u8 *ptr, u32 len)
{
    WMI_BTCOEX_STATS_EVENT *pBtcoexStats = (WMI_BTCOEX_STATS_EVENT *)ptr;

    AR_DEBUG_PRINTF(ATH_DEBUG_INFO,("AR6000 BTCOEX CONFIG EVENT \n"));

    memcpy(&ar->arBtcoexStats, pBtcoexStats, sizeof(WMI_BTCOEX_STATS_EVENT));

    if (ar->statsUpdatePending) {
         ar->statsUpdatePending = false;
        wake_up(&arEvent);
    }

}
