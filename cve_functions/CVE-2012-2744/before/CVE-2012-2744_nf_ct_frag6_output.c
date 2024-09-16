void nf_ct_frag6_output(unsigned int hooknum, struct sk_buff *skb,
			struct net_device *in, struct net_device *out,
			int (*okfn)(struct sk_buff *))
{
	struct sk_buff *s, *s2;

	for (s = NFCT_FRAG6_CB(skb)->orig; s;) {
		nf_conntrack_put_reasm(s->nfct_reasm);
		nf_conntrack_get_reasm(skb);
		s->nfct_reasm = skb;

		s2 = s->next;
		s->next = NULL;

		NF_HOOK_THRESH(PF_INET6, hooknum, s, in, out, okfn,
			       NF_IP6_PRI_CONNTRACK_DEFRAG + 1);
		s = s2;
	}
	nf_conntrack_put_reasm(skb);
}
