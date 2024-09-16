ar6000_snrThresholdEvent_rx(void *devt, WMI_SNR_THRESHOLD_VAL newThreshold, u8 snr)
{
    WMI_SNR_THRESHOLD_EVENT event;

    event.range = newThreshold;
    event.snr = snr;
}
