static int unsubscribe_port(struct snd_seq_client *client,
			    struct snd_seq_client_port *port,
			    struct snd_seq_port_subs_info *grp,
			    struct snd_seq_port_subscribe *info,
			    int send_ack)
{
	int err = 0;

	if (! grp->count)
		return -EINVAL;
	grp->count--;
	if (grp->close && grp->count == 0)
		err = grp->close(port->private_data, info);
	if (send_ack && client->type == USER_CLIENT)
		snd_seq_client_notify_subscription(port->addr.client, port->addr.port,
						   info, SNDRV_SEQ_EVENT_PORT_UNSUBSCRIBED);
	module_put(port->owner);
	return err;
}
