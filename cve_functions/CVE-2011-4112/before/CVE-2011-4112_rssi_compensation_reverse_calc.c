s16 rssi_compensation_reverse_calc(struct ar6_softc *ar, s16 rssi, bool Above)
{
    s16 i;

    if (ar->arBssChannel > 5000)
    {
        if (rssi_compensation_param.enable)
        {
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, (">>> 11a\n"));
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi before rev compensation  = %d\n", rssi));
            rssi = rssi * 100;
            rssi = (rssi - rssi_compensation_param.a_param_b) / rssi_compensation_param.a_param_a;
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi after rev compensation = %d\n", rssi));
        }
    }
    else
    {
        if (rssi_compensation_param.enable)
        {
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, (">>> 11bg\n"));
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi before rev compensation  = %d\n", rssi));

            if (Above) {
                for (i=95; i>=0; i--) {
                    if (rssi <=  rssi_compensation_table[i]) {
                        rssi = 0 - i;
                        break;
                    }
                }
            } else {
                for (i=0; i<=95; i++) {
                    if (rssi >=  rssi_compensation_table[i]) {
                        rssi = 0 - i;
                        break;
                    }
                }
            }
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi after rev compensation = %d\n", rssi));
        }
    }

    return rssi;
}
