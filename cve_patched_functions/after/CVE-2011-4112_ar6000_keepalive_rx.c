ar6000_keepalive_rx(void *devt, u8 configured)
{
    struct ar6_softc *ar = (struct ar6_softc *)devt;

    ar->arKeepaliveConfigured = configured;
    wake_up(&arEvent);
}
