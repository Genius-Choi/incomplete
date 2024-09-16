int cipso_v4_skbuff_getattr(const struct sk_buff *skb,
			    struct netlbl_lsm_secattr *secattr)
{
	return cipso_v4_getattr(CIPSO_V4_OPTPTR(skb), secattr);
}
