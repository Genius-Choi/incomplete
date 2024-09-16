static int fwnet_header_parse(const struct sk_buff *skb, unsigned char *haddr)
{
	memcpy(haddr, skb->dev->dev_addr, FWNET_ALEN);

	return FWNET_ALEN;
}
