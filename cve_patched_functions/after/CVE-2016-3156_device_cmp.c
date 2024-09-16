static int device_cmp(struct nf_conn *i, void *ifindex)
{
	const struct nf_conn_nat *nat = nfct_nat(i);

	if (!nat)
		return 0;
	if (nf_ct_l3num(i) != NFPROTO_IPV4)
		return 0;
	return nat->masq_index == (int)(long)ifindex;
}
