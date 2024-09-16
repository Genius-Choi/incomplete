free_config_peers(
	config_tree *ptree
	)
{
	peer_node *curr_peer;

	if (ptree->peers != NULL) {
		while (1) {
			UNLINK_FIFO(curr_peer, *ptree->peers, link);
			if (NULL == curr_peer)
				break;
			destroy_address_node(curr_peer->addr);
			destroy_attr_val_fifo(curr_peer->peerflags);
			free(curr_peer);
		}
		free(ptree->peers);
		ptree->peers = NULL;
	}
}
