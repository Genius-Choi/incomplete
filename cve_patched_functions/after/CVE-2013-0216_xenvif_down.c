static void xenvif_down(struct xenvif *vif)
{
	disable_irq(vif->irq);
	xen_netbk_deschedule_xenvif(vif);
	xen_netbk_remove_xenvif(vif);
}
