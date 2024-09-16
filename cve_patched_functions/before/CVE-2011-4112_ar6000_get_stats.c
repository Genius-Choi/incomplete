ar6000_get_stats(struct net_device *dev)
{
    struct ar6_softc *ar = (struct ar6_softc *)ar6k_priv(dev);
    return &ar->arNetStats;
}
