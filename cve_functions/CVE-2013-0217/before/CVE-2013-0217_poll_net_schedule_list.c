static struct xenvif *poll_net_schedule_list(struct xen_netbk *netbk)
{
	struct xenvif *vif = NULL;

	spin_lock_irq(&netbk->net_schedule_list_lock);
	if (list_empty(&netbk->net_schedule_list))
		goto out;

	vif = list_first_entry(&netbk->net_schedule_list,
			       struct xenvif, schedule_list);
	if (!vif)
		goto out;

	xenvif_get(vif);

	remove_from_net_schedule_list(vif);
out:
	spin_unlock_irq(&netbk->net_schedule_list_lock);
	return vif;
}
