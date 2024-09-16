static int __init initialize_hashrnd(void)
{
	get_random_bytes(&skb_tx_hashrnd, sizeof(skb_tx_hashrnd));
	return 0;
}
