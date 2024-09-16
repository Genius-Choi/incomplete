static int __on_net_schedule_list(struct xenvif *vif)
{
	return !list_empty(&vif->schedule_list);
}
