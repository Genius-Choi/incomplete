static unsigned int pkt_type_offset(void)
{
	struct sk_buff skb_probe = { .pkt_type = ~0, };
	u8 *ct = (u8 *) &skb_probe;
	unsigned int off;

	for (off = 0; off < sizeof(struct sk_buff); off++) {
		if (ct[off] == PKT_TYPE_MAX)
			return off;
	}

	pr_err_once("Please fix %s, as pkt_type couldn't be found!\n", __func__);
	return -1;
}
