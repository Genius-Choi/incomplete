static inline bool llc_dgram_match(const struct llc_sap *sap,
				   const struct llc_addr *laddr,
				   const struct sock *sk)
{
     struct llc_sock *llc = llc_sk(sk);

     return sk->sk_type == SOCK_DGRAM &&
	  llc->laddr.lsap == laddr->lsap &&
	  ether_addr_equal(llc->laddr.mac, laddr->mac);
}
