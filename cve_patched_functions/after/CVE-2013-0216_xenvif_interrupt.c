static irqreturn_t xenvif_interrupt(int irq, void *dev_id)
{
	struct xenvif *vif = dev_id;

	if (vif->netbk == NULL)
		return IRQ_NONE;

	xen_netbk_schedule_xenvif(vif);

	if (xenvif_rx_schedulable(vif))
		netif_wake_queue(vif->dev);

	return IRQ_HANDLED;
}
