static struct sock *__llc_lookup(struct llc_sap *sap,
				 struct llc_addr *daddr,
				 struct llc_addr *laddr)
{
	struct sock *sk = __llc_lookup_established(sap, daddr, laddr);

	return sk ? : llc_lookup_listener(sap, laddr);
}
