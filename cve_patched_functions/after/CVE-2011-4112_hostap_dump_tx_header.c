void hostap_dump_tx_header(const char *name, const struct hfa384x_tx_frame *tx)
{
	u16 fc;

	printk(KERN_DEBUG "%s: TX status=0x%04x retry_count=%d tx_rate=%d "
	       "tx_control=0x%04x; jiffies=%ld\n",
	       name, __le16_to_cpu(tx->status), tx->retry_count, tx->tx_rate,
	       __le16_to_cpu(tx->tx_control), jiffies);

	fc = __le16_to_cpu(tx->frame_control);
	printk(KERN_DEBUG "   FC=0x%04x (type=%d:%d) dur=0x%04x seq=0x%04x "
	       "data_len=%d%s%s\n",
	       fc, (fc & IEEE80211_FCTL_FTYPE) >> 2,
	       (fc & IEEE80211_FCTL_STYPE) >> 4,
	       __le16_to_cpu(tx->duration_id), __le16_to_cpu(tx->seq_ctrl),
	       __le16_to_cpu(tx->data_len),
	       fc & IEEE80211_FCTL_TODS ? " [ToDS]" : "",
	       fc & IEEE80211_FCTL_FROMDS ? " [FromDS]" : "");

	printk(KERN_DEBUG "   A1=%pM A2=%pM A3=%pM A4=%pM\n",
	       tx->addr1, tx->addr2, tx->addr3, tx->addr4);

	printk(KERN_DEBUG "   dst=%pM src=%pM len=%d\n",
	       tx->dst_addr, tx->src_addr,
	       __be16_to_cpu(tx->len));
}
