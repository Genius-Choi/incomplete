void llc_conn_rtn_pdu(struct sock *sk, struct sk_buff *skb)
{
	struct llc_conn_state_ev *ev = llc_conn_ev(skb);

	ev->ind_prim = LLC_DATA_PRIM;
}
