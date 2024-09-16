static void xenvif_up(struct xenvif *vif)
{
	xen_netbk_add_xenvif(vif);
	enable_irq(vif->irq);
	xen_netbk_check_rx_xenvif(vif);
}
