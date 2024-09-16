static void fwnet_remove_peer(struct fwnet_peer *peer, struct fwnet_device *dev)
{
	struct fwnet_partial_datagram *pd, *pd_next;

	spin_lock_irq(&dev->lock);
	list_del(&peer->peer_link);
	dev->peer_count--;
	set_carrier_state(dev);
	spin_unlock_irq(&dev->lock);

	list_for_each_entry_safe(pd, pd_next, &peer->pd_list, pd_link)
		fwnet_pd_delete(pd);

	kfree(peer);
}
