static void tg3_free_rings(struct tg3 *tp)
{
	int i, j;

	for (j = 0; j < tp->irq_cnt; j++) {
		struct tg3_napi *tnapi = &tp->napi[j];

		tg3_rx_prodring_free(tp, &tnapi->prodring);

		if (!tnapi->tx_buffers)
			continue;

		for (i = 0; i < TG3_TX_RING_SIZE; i++) {
			struct sk_buff *skb = tnapi->tx_buffers[i].skb;

			if (!skb)
				continue;

			tg3_tx_skb_unmap(tnapi, i,
					 skb_shinfo(skb)->nr_frags - 1);

			dev_kfree_skb_any(skb);
		}
		netdev_tx_reset_queue(netdev_get_tx_queue(tp->dev, j));
	}
}
