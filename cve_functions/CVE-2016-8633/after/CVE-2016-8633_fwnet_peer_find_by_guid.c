static struct fwnet_peer *fwnet_peer_find_by_guid(struct fwnet_device *dev,
						  u64 guid)
{
	struct fwnet_peer *peer;

	list_for_each_entry(peer, &dev->peer_list, peer_link)
		if (peer->guid == guid)
			return peer;

	return NULL;
}
