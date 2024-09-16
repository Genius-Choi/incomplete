void xen_netbk_deschedule_xenvif(struct xenvif *vif)
{
	struct xen_netbk *netbk = vif->netbk;
	spin_lock_irq(&netbk->net_schedule_list_lock);
	remove_from_net_schedule_list(vif);
	spin_unlock_irq(&netbk->net_schedule_list_lock);
}
