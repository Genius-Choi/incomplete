struct snd_seq_client_port *snd_seq_port_query_nearest(struct snd_seq_client *client,
						       struct snd_seq_port_info *pinfo)
{
	int num;
	struct snd_seq_client_port *port, *found;

	num = pinfo->addr.port;
	found = NULL;
	read_lock(&client->ports_lock);
	list_for_each_entry(port, &client->ports_list_head, list) {
		if (port->addr.port < num)
			continue;
		if (port->addr.port == num) {
			found = port;
			break;
		}
		if (found == NULL || port->addr.port < found->addr.port)
			found = port;
	}
	if (found) {
		if (found->closing)
			found = NULL;
		else
			snd_use_lock_use(&found->use_lock);
	}
	read_unlock(&client->ports_lock);
	return found;
}
