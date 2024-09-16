static int pegasus_probe(struct usb_interface *intf,
			 const struct usb_device_id *id)
{
	struct usb_device *dev = interface_to_usbdev(intf);
	struct net_device *net;
	pegasus_t *pegasus;
	int dev_index = id - pegasus_ids;
	int res = -ENOMEM;

	if (pegasus_blacklisted(dev))
		return -ENODEV;

	if (pegasus_count == 0) {
		pegasus_workqueue = alloc_workqueue("pegasus", WQ_MEM_RECLAIM,
						    0);
		if (!pegasus_workqueue)
			return -ENOMEM;
	}
	pegasus_count++;

	net = alloc_etherdev(sizeof(struct pegasus));
	if (!net)
		goto out;

	pegasus = netdev_priv(net);
	pegasus->dev_index = dev_index;

	res = alloc_urbs(pegasus);
	if (res < 0) {
		dev_err(&intf->dev, "can't allocate %s\n", "urbs");
		goto out1;
	}

	tasklet_init(&pegasus->rx_tl, rx_fixup, (unsigned long) pegasus);

	INIT_DELAYED_WORK(&pegasus->carrier_check, check_carrier);

	pegasus->intf = intf;
	pegasus->usb = dev;
	pegasus->net = net;


	net->watchdog_timeo = PEGASUS_TX_TIMEOUT;
	net->netdev_ops = &pegasus_netdev_ops;
	net->ethtool_ops = &ops;
	pegasus->mii.dev = net;
	pegasus->mii.mdio_read = mdio_read;
	pegasus->mii.mdio_write = mdio_write;
	pegasus->mii.phy_id_mask = 0x1f;
	pegasus->mii.reg_num_mask = 0x1f;
	pegasus->msg_enable = netif_msg_init(msg_level, NETIF_MSG_DRV
				| NETIF_MSG_PROBE | NETIF_MSG_LINK);

	pegasus->features = usb_dev_id[dev_index].private;
	get_interrupt_interval(pegasus);
	if (reset_mac(pegasus)) {
		dev_err(&intf->dev, "can't reset MAC\n");
		res = -EIO;
		goto out2;
	}
	set_ethernet_addr(pegasus);
	if (pegasus->features & PEGASUS_II) {
		dev_info(&intf->dev, "setup Pegasus II specific registers\n");
		setup_pegasus_II(pegasus);
	}
	pegasus->phy = mii_phy_probe(pegasus);
	if (pegasus->phy == 0xff) {
		dev_warn(&intf->dev, "can't locate MII phy, using default\n");
		pegasus->phy = 1;
	}
	pegasus->mii.phy_id = pegasus->phy;
	usb_set_intfdata(intf, pegasus);
	SET_NETDEV_DEV(net, &intf->dev);
	pegasus_reset_wol(net);
	res = register_netdev(net);
	if (res)
		goto out3;
	queue_delayed_work(pegasus_workqueue, &pegasus->carrier_check,
			   CARRIER_CHECK_DELAY);
	dev_info(&intf->dev, "%s, %s, %pM\n", net->name,
		 usb_dev_id[dev_index].name, net->dev_addr);
	return 0;

out3:
	usb_set_intfdata(intf, NULL);
out2:
	free_all_urbs(pegasus);
out1:
	free_netdev(net);
out:
	pegasus_dec_workqueue();
	return res;
}
