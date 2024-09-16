static int wll_header_parse(const struct sk_buff *skb, unsigned char *haddr)
{
	memcpy(haddr, skb_mac_header(skb) + 10, ETH_ALEN);
	return ETH_ALEN;
}
