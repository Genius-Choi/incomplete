static void tg3_tx(struct tg3_napi *tnapi)
{
	struct tg3 *tp = tnapi->tp;
	u32 hw_idx = tnapi->hw_status->idx[0].tx_consumer;
	u32 sw_idx = tnapi->tx_cons;
	struct netdev_queue *txq;
	int index = tnapi - tp->napi;
	unsigned int pkts_compl = 0, bytes_compl = 0;

	if (tg3_flag(tp, ENABLE_TSS))
		index--;

	txq = netdev_get_tx_queue(tp->dev, index);

	while (sw_idx != hw_idx) {
		struct tg3_tx_ring_info *ri = &tnapi->tx_buffers[sw_idx];
		struct sk_buff *skb = ri->skb;
		int i, tx_bug = 0;

		if (unlikely(skb == NULL)) {
			tg3_tx_recover(tp);
			return;
		}

		if (tnapi->tx_ring[sw_idx].len_flags & TXD_FLAG_HWTSTAMP) {
			struct skb_shared_hwtstamps timestamp;
			u64 hwclock = tr32(TG3_TX_TSTAMP_LSB);
			hwclock |= (u64)tr32(TG3_TX_TSTAMP_MSB) << 32;

			tg3_hwclock_to_timestamp(tp, hwclock, &timestamp);

			skb_tstamp_tx(skb, &timestamp);
		}

		pci_unmap_single(tp->pdev,
				 dma_unmap_addr(ri, mapping),
				 skb_headlen(skb),
				 PCI_DMA_TODEVICE);

		ri->skb = NULL;

		while (ri->fragmented) {
			ri->fragmented = false;
			sw_idx = NEXT_TX(sw_idx);
			ri = &tnapi->tx_buffers[sw_idx];
		}

		sw_idx = NEXT_TX(sw_idx);

		for (i = 0; i < skb_shinfo(skb)->nr_frags; i++) {
			ri = &tnapi->tx_buffers[sw_idx];
			if (unlikely(ri->skb != NULL || sw_idx == hw_idx))
				tx_bug = 1;

			pci_unmap_page(tp->pdev,
				       dma_unmap_addr(ri, mapping),
				       skb_frag_size(&skb_shinfo(skb)->frags[i]),
				       PCI_DMA_TODEVICE);

			while (ri->fragmented) {
				ri->fragmented = false;
				sw_idx = NEXT_TX(sw_idx);
				ri = &tnapi->tx_buffers[sw_idx];
			}

			sw_idx = NEXT_TX(sw_idx);
		}

		pkts_compl++;
		bytes_compl += skb->len;

		dev_kfree_skb(skb);

		if (unlikely(tx_bug)) {
			tg3_tx_recover(tp);
			return;
		}
	}

	netdev_tx_completed_queue(txq, pkts_compl, bytes_compl);

	tnapi->tx_cons = sw_idx;

	/* Need to make the tx_cons update visible to tg3_start_xmit()
	 * before checking for netif_queue_stopped().  Without the
	 * memory barrier, there is a small possibility that tg3_start_xmit()
	 * will miss it and cause the queue to be stopped forever.
	 */
	smp_mb();

	if (unlikely(netif_tx_queue_stopped(txq) &&
		     (tg3_tx_avail(tnapi) > TG3_TX_WAKEUP_THRESH(tnapi)))) {
		__netif_tx_lock(txq, smp_processor_id());
		if (netif_tx_queue_stopped(txq) &&
		    (tg3_tx_avail(tnapi) > TG3_TX_WAKEUP_THRESH(tnapi)))
			netif_tx_wake_queue(txq);
		__netif_tx_unlock(txq);
	}
}
