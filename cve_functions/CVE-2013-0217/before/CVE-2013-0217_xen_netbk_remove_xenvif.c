void xen_netbk_remove_xenvif(struct xenvif *vif)
{
	struct xen_netbk *netbk = vif->netbk;
	vif->netbk = NULL;
	atomic_dec(&netbk->netfront_count);
}
