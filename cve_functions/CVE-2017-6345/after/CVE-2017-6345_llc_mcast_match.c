static inline bool llc_mcast_match(const struct llc_sap *sap,
				   const struct llc_addr *laddr,
				   const struct sk_buff *skb,
				   const struct sock *sk)
{
     struct llc_sock *llc = llc_sk(sk);

     return sk->sk_type == SOCK_DGRAM &&
	  llc->laddr.lsap == laddr->lsap &&
	  llc->dev == skb->dev;
}
