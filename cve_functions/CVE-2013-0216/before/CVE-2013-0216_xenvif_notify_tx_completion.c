void xenvif_notify_tx_completion(struct xenvif *vif)
{
	if (netif_queue_stopped(vif->dev) && xenvif_rx_schedulable(vif))
		netif_wake_queue(vif->dev);
}
