s16 rssi_compensation_calc(struct ar6_softc *ar, s16 rssi)
{
    if (ar->arBssChannel > 5000)
    {
        if (rssi_compensation_param.enable)
        {
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, (">>> 11a\n"));
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi before compensation  = %d\n", rssi));
            rssi = rssi * rssi_compensation_param.a_param_a + rssi_compensation_param.a_param_b;
            rssi = (rssi-50) /100;
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi after compensation = %d\n", rssi));
        }
    }
    else
    {
        if (rssi_compensation_param.enable)
        {
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, (">>> 11bg\n"));
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi before compensation  = %d\n", rssi));
            rssi = rssi * rssi_compensation_param.bg_param_a + rssi_compensation_param.bg_param_b;
            rssi = (rssi-50) /100;
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi after compensation = %d\n", rssi));
        }
    }

    return rssi;
}
