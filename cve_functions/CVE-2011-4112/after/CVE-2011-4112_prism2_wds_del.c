int prism2_wds_del(local_info_t *local, u8 *remote_addr,
		   int rtnl_locked, int do_not_remove)
{
	unsigned long flags;
	struct list_head *ptr;
	struct hostap_interface *iface, *selected = NULL;

	write_lock_irqsave(&local->iface_lock, flags);
	list_for_each(ptr, &local->hostap_interfaces) {
		iface = list_entry(ptr, struct hostap_interface, list);
		if (iface->type != HOSTAP_INTERFACE_WDS)
			continue;

		if (memcmp(iface->u.wds.remote_addr, remote_addr,
			   ETH_ALEN) == 0) {
			selected = iface;
			break;
		}
	}
	if (selected && !do_not_remove)
		list_del(&selected->list);
	write_unlock_irqrestore(&local->iface_lock, flags);

	if (selected) {
		if (do_not_remove)
			memset(selected->u.wds.remote_addr, 0, ETH_ALEN);
		else {
			hostap_remove_interface(selected->dev, rtnl_locked, 0);
			local->wds_connections--;
		}
	}

	return selected ? 0 : -ENODEV;
}
