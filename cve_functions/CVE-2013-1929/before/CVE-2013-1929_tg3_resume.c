static int tg3_resume(struct device *device)
{
	struct pci_dev *pdev = to_pci_dev(device);
	struct net_device *dev = pci_get_drvdata(pdev);
	struct tg3 *tp = netdev_priv(dev);
	int err;

	if (!netif_running(dev))
		return 0;

	netif_device_attach(dev);

	tg3_full_lock(tp, 0);

	tg3_flag_set(tp, INIT_COMPLETE);
	err = tg3_restart_hw(tp, 1);
	if (err)
		goto out;

	tg3_timer_start(tp);

	tg3_netif_start(tp);

out:
	tg3_full_unlock(tp);

	if (!err)
		tg3_phy_start(tp);

	return err;
}
