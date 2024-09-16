static int tg3_suspend(struct device *device)
{
	struct pci_dev *pdev = to_pci_dev(device);
	struct net_device *dev = pci_get_drvdata(pdev);
	struct tg3 *tp = netdev_priv(dev);
	int err;

	if (!netif_running(dev))
		return 0;

	tg3_reset_task_cancel(tp);
	tg3_phy_stop(tp);
	tg3_netif_stop(tp);

	tg3_timer_stop(tp);

	tg3_full_lock(tp, 1);
	tg3_disable_ints(tp);
	tg3_full_unlock(tp);

	netif_device_detach(dev);

	tg3_full_lock(tp, 0);
	tg3_halt(tp, RESET_KIND_SHUTDOWN, 1);
	tg3_flag_clear(tp, INIT_COMPLETE);
	tg3_full_unlock(tp);

	err = tg3_power_down_prepare(tp);
	if (err) {
		int err2;

		tg3_full_lock(tp, 0);

		tg3_flag_set(tp, INIT_COMPLETE);
		err2 = tg3_restart_hw(tp, 1);
		if (err2)
			goto out;

		tg3_timer_start(tp);

		netif_device_attach(dev);
		tg3_netif_start(tp);

out:
		tg3_full_unlock(tp);

		if (!err2)
			tg3_phy_start(tp);
	}

	return err;
}
