static void disconnect_timer_handler(unsigned long ptr)
{
    struct net_device *dev = (struct net_device *)ptr;
    struct ar6_softc *ar = (struct ar6_softc *)ar6k_priv(dev);

    A_UNTIMEOUT(&ar->disconnect_timer);

    ar6000_init_profile_info(ar);
    ar6000_disconnect(ar);
}
