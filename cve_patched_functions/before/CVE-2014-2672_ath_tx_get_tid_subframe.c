ath_tx_get_tid_subframe(struct ath_softc *sc, struct ath_txq *txq,
			struct ath_atx_tid *tid, struct sk_buff_head **q)
{
	struct ieee80211_tx_info *tx_info;
	struct ath_frame_info *fi;
	struct sk_buff *skb;
	struct ath_buf *bf;
	u16 seqno;

	while (1) {
		*q = &tid->retry_q;
		if (skb_queue_empty(*q))
			*q = &tid->buf_q;

		skb = skb_peek(*q);
		if (!skb)
			break;

		fi = get_frame_info(skb);
		bf = fi->bf;
		if (!fi->bf)
			bf = ath_tx_setup_buffer(sc, txq, tid, skb);
		else
			bf->bf_state.stale = false;

		if (!bf) {
			__skb_unlink(skb, *q);
			ath_txq_skb_done(sc, txq, skb);
			ieee80211_free_txskb(sc->hw, skb);
			continue;
		}

		bf->bf_next = NULL;
		bf->bf_lastbf = bf;

		tx_info = IEEE80211_SKB_CB(skb);
		tx_info->flags &= ~IEEE80211_TX_CTL_CLEAR_PS_FILT;
		if (!(tx_info->flags & IEEE80211_TX_CTL_AMPDU)) {
			bf->bf_state.bf_type = 0;
			return bf;
		}

		bf->bf_state.bf_type = BUF_AMPDU | BUF_AGGR;
		seqno = bf->bf_state.seqno;

		/* do not step over block-ack window */
		if (!BAW_WITHIN(tid->seq_start, tid->baw_size, seqno))
			break;

		if (tid->bar_index > ATH_BA_INDEX(tid->seq_start, seqno)) {
			struct ath_tx_status ts = {};
			struct list_head bf_head;

			INIT_LIST_HEAD(&bf_head);
			list_add(&bf->list, &bf_head);
			__skb_unlink(skb, *q);
			ath_tx_update_baw(sc, tid, seqno);
			ath_tx_complete_buf(sc, bf, txq, &bf_head, &ts, 0);
			continue;
		}

		return bf;
	}

	return NULL;
}
