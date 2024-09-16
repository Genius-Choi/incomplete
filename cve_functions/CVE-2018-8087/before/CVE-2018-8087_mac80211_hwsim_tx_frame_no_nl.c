static bool mac80211_hwsim_tx_frame_no_nl(struct ieee80211_hw *hw,
					  struct sk_buff *skb,
					  struct ieee80211_channel *chan)
{
	struct mac80211_hwsim_data *data = hw->priv, *data2;
	bool ack = false;
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct ieee80211_rx_status rx_status;
	u64 now;

	memset(&rx_status, 0, sizeof(rx_status));
	rx_status.flag |= RX_FLAG_MACTIME_START;
	rx_status.freq = chan->center_freq;
	rx_status.band = chan->band;
	if (info->control.rates[0].flags & IEEE80211_TX_RC_VHT_MCS) {
		rx_status.rate_idx =
			ieee80211_rate_get_vht_mcs(&info->control.rates[0]);
		rx_status.nss =
			ieee80211_rate_get_vht_nss(&info->control.rates[0]);
		rx_status.encoding = RX_ENC_VHT;
	} else {
		rx_status.rate_idx = info->control.rates[0].idx;
		if (info->control.rates[0].flags & IEEE80211_TX_RC_MCS)
			rx_status.encoding = RX_ENC_HT;
	}
	if (info->control.rates[0].flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		rx_status.bw = RATE_INFO_BW_40;
	else if (info->control.rates[0].flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		rx_status.bw = RATE_INFO_BW_80;
	else if (info->control.rates[0].flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
		rx_status.bw = RATE_INFO_BW_160;
	else
		rx_status.bw = RATE_INFO_BW_20;
	if (info->control.rates[0].flags & IEEE80211_TX_RC_SHORT_GI)
		rx_status.enc_flags |= RX_ENC_FLAG_SHORT_GI;
	/* TODO: simulate real signal strength (and optional packet loss) */
	rx_status.signal = -50;
	if (info->control.vif)
		rx_status.signal += info->control.vif->bss_conf.txpower;

	if (data->ps != PS_DISABLED)
		hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);

	/* release the skb's source info */
	skb_orphan(skb);
	skb_dst_drop(skb);
	skb->mark = 0;
	secpath_reset(skb);
	nf_reset(skb);

	/*
	 * Get absolute mactime here so all HWs RX at the "same time", and
	 * absolute TX time for beacon mactime so the timestamp matches.
	 * Giving beacons a different mactime than non-beacons looks messy, but
	 * it helps the Toffset be exact and a ~10us mactime discrepancy
	 * probably doesn't really matter.
	 */
	if (ieee80211_is_beacon(hdr->frame_control) ||
	    ieee80211_is_probe_resp(hdr->frame_control))
		now = data->abs_bcn_ts;
	else
		now = mac80211_hwsim_get_tsf_raw();

	/* Copy skb to all enabled radios that are on the current frequency */
	spin_lock(&hwsim_radio_lock);
	list_for_each_entry(data2, &hwsim_radios, list) {
		struct sk_buff *nskb;
		struct tx_iter_data tx_iter_data = {
			.receive = false,
			.channel = chan,
		};

		if (data == data2)
			continue;

		if (!data2->started || (data2->idle && !data2->tmp_chan) ||
		    !hwsim_ps_rx_ok(data2, skb))
			continue;

		if (!(data->group & data2->group))
			continue;

		if (data->netgroup != data2->netgroup)
			continue;

		if (!hwsim_chans_compat(chan, data2->tmp_chan) &&
		    !hwsim_chans_compat(chan, data2->channel)) {
			ieee80211_iterate_active_interfaces_atomic(
				data2->hw, IEEE80211_IFACE_ITER_NORMAL,
				mac80211_hwsim_tx_iter, &tx_iter_data);
			if (!tx_iter_data.receive)
				continue;
		}

		/*
		 * reserve some space for our vendor and the normal
		 * radiotap header, since we're copying anyway
		 */
		if (skb->len < PAGE_SIZE && paged_rx) {
			struct page *page = alloc_page(GFP_ATOMIC);

			if (!page)
				continue;

			nskb = dev_alloc_skb(128);
			if (!nskb) {
				__free_page(page);
				continue;
			}

			memcpy(page_address(page), skb->data, skb->len);
			skb_add_rx_frag(nskb, 0, page, 0, skb->len, skb->len);
		} else {
			nskb = skb_copy(skb, GFP_ATOMIC);
			if (!nskb)
				continue;
		}

		if (mac80211_hwsim_addr_match(data2, hdr->addr1))
			ack = true;

		rx_status.mactime = now + data2->tsf_offset;

		memcpy(IEEE80211_SKB_RXCB(nskb), &rx_status, sizeof(rx_status));

		mac80211_hwsim_add_vendor_rtap(nskb);

		data2->rx_pkts++;
		data2->rx_bytes += nskb->len;
		ieee80211_rx_irqsafe(data2->hw, nskb);
	}
	spin_unlock(&hwsim_radio_lock);

	return ack;
}
