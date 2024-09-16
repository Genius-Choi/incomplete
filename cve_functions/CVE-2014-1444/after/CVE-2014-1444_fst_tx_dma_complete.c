fst_tx_dma_complete(struct fst_card_info *card, struct fst_port_info *port,
		    int len, int txpos)
{
	struct net_device *dev = port_to_dev(port);

	/*
	 * Everything is now set, just tell the card to go
	 */
	dbg(DBG_TX, "fst_tx_dma_complete\n");
	FST_WRB(card, txDescrRing[port->index][txpos].bits,
		DMA_OWN | TX_STP | TX_ENP);
	dev->stats.tx_packets++;
	dev->stats.tx_bytes += len;
	dev->trans_start = jiffies;
}
