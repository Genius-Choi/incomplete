void hostap_dump_rx_header(const char *name, const struct hfa384x_rx_frame *rx)
{
	u16 status, fc;

	status = __le16_to_cpu(rx->status);

	printk(KERN_DEBUG "%s: RX status=0x%04x (port=%d, type=%d, "
	       "fcserr=%d) silence=%d signal=%d rate=%d rxflow=%d; "
	       "jiffies=%ld\n",
	       name, status, (status >> 8) & 0x07, status >> 13, status & 1,
	       rx->silence, rx->signal, rx->rate, rx->rxflow, jiffies);

	fc = __le16_to_cpu(rx->frame_control);
	printk(KERN_DEBUG "   FC=0x%04x (type=%d:%d) dur=0x%04x seq=0x%04x "
	       "data_len=%d%s%s\n",
	       fc, (fc & IEEE80211_FCTL_FTYPE) >> 2,
	       (fc & IEEE80211_FCTL_STYPE) >> 4,
	       __le16_to_cpu(rx->duration_id), __le16_to_cpu(rx->seq_ctrl),
	       __le16_to_cpu(rx->data_len),
	       fc & IEEE80211_FCTL_TODS ? " [ToDS]" : "",
	       fc & IEEE80211_FCTL_FROMDS ? " [FromDS]" : "");

	printk(KERN_DEBUG "   A1=%pM A2=%pM A3=%pM A4=%pM\n",
	       rx->addr1, rx->addr2, rx->addr3, rx->addr4);

	printk(KERN_DEBUG "   dst=%pM src=%pM len=%d\n",
	       rx->dst_addr, rx->src_addr,
	       __be16_to_cpu(rx->len));
}
