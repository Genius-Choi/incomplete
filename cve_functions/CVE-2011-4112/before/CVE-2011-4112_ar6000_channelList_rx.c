ar6000_channelList_rx(void *devt, s8 numChan, u16 *chanList)
{
    struct ar6_softc *ar = (struct ar6_softc *)devt;

    memcpy(ar->arChannelList, chanList, numChan * sizeof (u16));
    ar->arNumChannels = numChan;

    wake_up(&arEvent);
}
