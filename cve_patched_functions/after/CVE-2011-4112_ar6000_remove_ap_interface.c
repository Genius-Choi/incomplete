int ar6000_remove_ap_interface(struct ar6_softc *ar)
{
    if (arApNetDev) {
        ar6000_stop_ap_interface(ar);

        unregister_netdev(arApNetDev);
        free_netdev(apApNetDev);

        A_PRINTF("Remove AP interface\n");
    }
    ar->arApDev = NULL;
    arApNetDev = NULL;

    
    return 0;
}
