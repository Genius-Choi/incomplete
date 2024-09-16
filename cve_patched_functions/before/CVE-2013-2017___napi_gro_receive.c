__napi_gro_receive(struct napi_struct *napi, struct sk_buff *skb)
{
	struct sk_buff *p;

	if (netpoll_rx_on(skb))
		return GRO_NORMAL;

	for (p = napi->gro_list; p; p = p->next) {
		NAPI_GRO_CB(p)->same_flow =
			(p->dev == skb->dev) &&
			!compare_ether_header(skb_mac_header(p),
					      skb_gro_mac_header(skb));
		NAPI_GRO_CB(p)->flush = 0;
	}

	return dev_gro_receive(napi, skb);
}
