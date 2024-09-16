ar6000_ac2_endpoint_id ( void * devt, u8 ac)
{
    struct ar6_softc *ar = (struct ar6_softc *) devt;
    return(arAc2EndpointID(ar, ac));
}
