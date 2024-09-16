static inline bool llc_estab_match(const struct llc_sap *sap,
				   const struct llc_addr *daddr,
				   const struct llc_addr *laddr,
				   const struct sock *sk)
{
	struct llc_sock *llc = llc_sk(sk);

	return llc->laddr.lsap == laddr->lsap &&
		llc->daddr.lsap == daddr->lsap &&
		ether_addr_equal(llc->laddr.mac, laddr->mac) &&
		ether_addr_equal(llc->daddr.mac, daddr->mac);
}
