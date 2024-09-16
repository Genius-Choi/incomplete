u8 ar6000_endpoint_id2_ac(void * devt, HTC_ENDPOINT_ID ep )
{
    struct ar6_softc *ar = (struct ar6_softc *) devt;
    return(arEndpoint2Ac(ar, ep ));
}
