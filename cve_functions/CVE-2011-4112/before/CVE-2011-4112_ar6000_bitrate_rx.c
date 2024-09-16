ar6000_bitrate_rx(void *devt, s32 rateKbps)
{
    struct ar6_softc *ar = (struct ar6_softc *)devt;

    ar->arBitRate = rateKbps;
    wake_up(&arEvent);
}
