static int fwnet_add_peer(struct fwnet_device *dev,
			  struct fw_unit *unit, struct fw_device *device)
{
	struct fwnet_peer *peer;

	peer = kmalloc(sizeof(*peer), GFP_KERNEL);
	if (!peer)
		return -ENOMEM;

	dev_set_drvdata(&unit->device, peer);

	peer->dev = dev;
	peer->guid = (u64)device->config_rom[3] << 32 | device->config_rom[4];
	INIT_LIST_HEAD(&peer->pd_list);
	peer->pdg_size = 0;
	peer->datagram_label = 0;
	peer->speed = device->max_speed;
	peer->max_payload = fwnet_max_payload(device->max_rec, peer->speed);

	peer->generation = device->generation;
	smp_rmb();
	peer->node_id = device->node_id;

	spin_lock_irq(&dev->lock);
	list_add_tail(&peer->peer_link, &dev->peer_list);
	dev->peer_count++;
	set_carrier_state(dev);
	spin_unlock_irq(&dev->lock);

	return 0;
}
