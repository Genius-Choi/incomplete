static struct fwnet_peer *fwnet_peer_find_by_node_id(struct fwnet_device *dev,
						int node_id, int generation)
{
	struct fwnet_peer *peer;

	list_for_each_entry(peer, &dev->peer_list, peer_link)
		if (peer->node_id    == node_id &&
		    peer->generation == generation)
			return peer;

	return NULL;
}
