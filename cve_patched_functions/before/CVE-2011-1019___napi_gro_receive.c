__napi_gro_receive(struct napi_struct *napi, struct sk_buff *skb)
{
	struct sk_buff *p;

	for (p = napi->gro_list; p; p = p->next) {
		unsigned long diffs;

		diffs = (unsigned long)p->dev ^ (unsigned long)skb->dev;
		diffs |= p->vlan_tci ^ skb->vlan_tci;
		diffs |= compare_ether_header(skb_mac_header(p),
					      skb_gro_mac_header(skb));
		NAPI_GRO_CB(p)->same_flow = !diffs;
		NAPI_GRO_CB(p)->flush = 0;
	}

	return dev_gro_receive(napi, skb);
}
