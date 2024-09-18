ar6000_txPwr_rx(void *devt, u8 txPwr)
{
    struct ar6_softc *ar = (struct ar6_softc *)devt;

    ar->arTxPwr = txPwr;
    wake_up(&arEvent);
}
