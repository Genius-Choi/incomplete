static void set_tx_flow_on(struct caifsock *cf_sk)
{
	 set_bit(TX_FLOW_ON_BIT,
		(void *) &cf_sk->flow_state);
}
