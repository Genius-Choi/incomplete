s32 rssi_compensation_calc_tcmd(u32 freq, s32 rssi, u32 totalPkt)
{

    if (freq > 5000)
    {
        if (rssi_compensation_param.enable)
        {
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, (">>> 11a\n"));
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi before compensation  = %d, totalPkt = %d\n", rssi,totalPkt));
            rssi = rssi * rssi_compensation_param.a_param_a + totalPkt * rssi_compensation_param.a_param_b;
            rssi = (rssi-50) /100;
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi after compensation = %d\n", rssi));
        }
    }
    else
    {
        if (rssi_compensation_param.enable)
        {
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, (">>> 11bg\n"));
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi before compensation  = %d, totalPkt = %d\n", rssi,totalPkt));
            rssi = rssi * rssi_compensation_param.bg_param_a + totalPkt * rssi_compensation_param.bg_param_b;
            rssi = (rssi-50) /100;
            AR_DEBUG_PRINTF(ATH_DEBUG_INFO, ("rssi after compensation = %d\n", rssi));
        }
    }

    return rssi;
}
