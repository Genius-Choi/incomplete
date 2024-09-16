void ar6000_set_numdataendpts(struct ar6_softc *ar, u32 num)
{
    A_ASSERT(num <= (HTC_MAILBOX_NUM_MAX - 1));
    ar->arNumDataEndPts = num;
}
