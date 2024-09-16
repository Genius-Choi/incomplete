static int tcp_v6_parse_md5_keys (struct sock *sk, char __user *optval,
				  int optlen)
{
	struct tcp_md5sig cmd;
	struct sockaddr_in6 *sin6 = (struct sockaddr_in6 *)&cmd.tcpm_addr;
	u8 *newkey;

	if (optlen < sizeof(cmd))
		return -EINVAL;

	if (copy_from_user(&cmd, optval, sizeof(cmd)))
		return -EFAULT;

	if (sin6->sin6_family != AF_INET6)
		return -EINVAL;

	if (!cmd.tcpm_keylen) {
		if (!tcp_sk(sk)->md5sig_info)
			return -ENOENT;
		if (ipv6_addr_v4mapped(&sin6->sin6_addr))
			return tcp_v4_md5_do_del(sk, sin6->sin6_addr.s6_addr32[3]);
		return tcp_v6_md5_do_del(sk, &sin6->sin6_addr);
	}

	if (cmd.tcpm_keylen > TCP_MD5SIG_MAXKEYLEN)
		return -EINVAL;

	if (!tcp_sk(sk)->md5sig_info) {
		struct tcp_sock *tp = tcp_sk(sk);
		struct tcp_md5sig_info *p;

		p = kzalloc(sizeof(struct tcp_md5sig_info), GFP_KERNEL);
		if (!p)
			return -ENOMEM;

		tp->md5sig_info = p;
		sk_nocaps_add(sk, NETIF_F_GSO_MASK);
	}

	newkey = kmemdup(cmd.tcpm_key, cmd.tcpm_keylen, GFP_KERNEL);
	if (!newkey)
		return -ENOMEM;
	if (ipv6_addr_v4mapped(&sin6->sin6_addr)) {
		return tcp_v4_md5_do_add(sk, sin6->sin6_addr.s6_addr32[3],
					 newkey, cmd.tcpm_keylen);
	}
	return tcp_v6_md5_do_add(sk, &sin6->sin6_addr, newkey, cmd.tcpm_keylen);
}
