ath_tx_tid_change_state(struct ath_softc *sc, struct ath_atx_tid *tid)
{
	struct ath_txq *txq = tid->ac->txq;
	struct ieee80211_tx_info *tx_info;
	struct sk_buff *skb, *tskb;
	struct ath_buf *bf;
	struct ath_frame_info *fi;

	skb_queue_walk_safe(&tid->buf_q, skb, tskb) {
		fi = get_frame_info(skb);
		bf = fi->bf;

		tx_info = IEEE80211_SKB_CB(skb);
		tx_info->flags &= ~IEEE80211_TX_CTL_AMPDU;

		if (bf)
			continue;

		bf = ath_tx_setup_buffer(sc, txq, tid, skb);
		if (!bf) {
			__skb_unlink(skb, &tid->buf_q);
			ath_txq_skb_done(sc, txq, skb);
			ieee80211_free_txskb(sc->hw, skb);
			continue;
		}
	}

}
