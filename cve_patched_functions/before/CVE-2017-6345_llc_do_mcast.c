static void llc_do_mcast(struct llc_sap *sap, struct sk_buff *skb,
			 struct sock **stack, int count)
{
	struct sk_buff *skb1;
	int i;

	for (i = 0; i < count; i++) {
		skb1 = skb_clone(skb, GFP_ATOMIC);
		if (!skb1) {
			sock_put(stack[i]);
			continue;
		}

		llc_sap_rcv(sap, skb1, stack[i]);
		sock_put(stack[i]);
	}
}
