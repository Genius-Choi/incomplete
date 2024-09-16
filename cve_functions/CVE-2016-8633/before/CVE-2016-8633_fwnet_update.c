static void fwnet_update(struct fw_unit *unit)
{
	struct fw_device *device = fw_parent_device(unit);
	struct fwnet_peer *peer = dev_get_drvdata(&unit->device);
	int generation;

	generation = device->generation;

	spin_lock_irq(&peer->dev->lock);
	peer->node_id    = device->node_id;
	peer->generation = generation;
	spin_unlock_irq(&peer->dev->lock);
}
