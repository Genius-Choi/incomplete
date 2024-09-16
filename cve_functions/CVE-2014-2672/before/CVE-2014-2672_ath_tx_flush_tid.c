static void ath_tx_flush_tid(struct ath_softc *sc, struct ath_atx_tid *tid)
{
	struct ath_txq *txq = tid->ac->txq;
	struct sk_buff *skb;
	struct ath_buf *bf;
	struct list_head bf_head;
	struct ath_tx_status ts;
	struct ath_frame_info *fi;
	bool sendbar = false;

	INIT_LIST_HEAD(&bf_head);

	memset(&ts, 0, sizeof(ts));

	while ((skb = __skb_dequeue(&tid->retry_q))) {
		fi = get_frame_info(skb);
		bf = fi->bf;
		if (!bf) {
			ath_txq_skb_done(sc, txq, skb);
			ieee80211_free_txskb(sc->hw, skb);
			continue;
		}

		if (fi->baw_tracked) {
			ath_tx_update_baw(sc, tid, bf->bf_state.seqno);
			sendbar = true;
		}

		list_add_tail(&bf->list, &bf_head);
		ath_tx_complete_buf(sc, bf, txq, &bf_head, &ts, 0);
	}

	if (sendbar) {
		ath_txq_unlock(sc, txq);
		ath_send_bar(tid, tid->seq_start);
		ath_txq_lock(sc, txq);
	}
}
