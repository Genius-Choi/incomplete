static int ieee80211_skb_resize(struct ieee80211_sub_if_data *sdata,
				struct sk_buff *skb,
				int head_need, bool may_encrypt)
{
	struct ieee80211_local *local = sdata->local;
	int tail_need = 0;

	if (may_encrypt && sdata->crypto_tx_tailroom_needed_cnt) {
		tail_need = IEEE80211_ENCRYPT_TAILROOM;
		tail_need -= skb_tailroom(skb);
		tail_need = max_t(int, tail_need, 0);
	}

	if (skb_cloned(skb))
		I802_DEBUG_INC(local->tx_expand_skb_head_cloned);
	else if (head_need || tail_need)
		I802_DEBUG_INC(local->tx_expand_skb_head);
	else
		return 0;

	if (pskb_expand_head(skb, head_need, tail_need, GFP_ATOMIC)) {
		wiphy_debug(local->hw.wiphy,
			    "failed to reallocate TX buffer\n");
		return -ENOMEM;
	}

	return 0;
}
