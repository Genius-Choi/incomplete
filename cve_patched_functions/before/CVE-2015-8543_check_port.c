static int check_port(__le16 port)
{
	struct sock *sk;

	if (port == 0)
		return -1;

	sk_for_each(sk, &dn_sk_hash[le16_to_cpu(port) & DN_SK_HASH_MASK]) {
		struct dn_scp *scp = DN_SK(sk);
		if (scp->addrloc == port)
			return -1;
	}
	return 0;
}
