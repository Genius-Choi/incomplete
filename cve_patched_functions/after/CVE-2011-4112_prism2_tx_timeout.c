static void prism2_tx_timeout(struct net_device *dev)
{
	struct hostap_interface *iface;
	local_info_t *local;
	struct hfa384x_regs regs;

	iface = netdev_priv(dev);
	local = iface->local;

	printk(KERN_WARNING "%s Tx timed out! Resetting card\n", dev->name);
	netif_stop_queue(local->dev);

	local->func->read_regs(dev, &regs);
	printk(KERN_DEBUG "%s: CMD=%04x EVSTAT=%04x "
	       "OFFSET0=%04x OFFSET1=%04x SWSUPPORT0=%04x\n",
	       dev->name, regs.cmd, regs.evstat, regs.offset0, regs.offset1,
	       regs.swsupport0);

	local->func->schedule_reset(local);
}
