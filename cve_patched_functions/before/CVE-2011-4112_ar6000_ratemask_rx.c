ar6000_ratemask_rx(void *devt, u32 ratemask)
{
    struct ar6_softc *ar = (struct ar6_softc *)devt;

    ar->arRateMask = ratemask;
    wake_up(&arEvent);
}
