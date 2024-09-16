static int xenvif_rx_schedulable(struct xenvif *vif)
{
	return xenvif_schedulable(vif) && !xen_netbk_rx_ring_full(vif);
}
