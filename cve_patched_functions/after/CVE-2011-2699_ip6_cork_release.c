static void ip6_cork_release(struct inet_sock *inet, struct ipv6_pinfo *np)
{
	if (np->cork.opt) {
		kfree(np->cork.opt->dst0opt);
		kfree(np->cork.opt->dst1opt);
		kfree(np->cork.opt->hopopt);
		kfree(np->cork.opt->srcrt);
		kfree(np->cork.opt);
		np->cork.opt = NULL;
	}

	if (inet->cork.base.dst) {
		dst_release(inet->cork.base.dst);
		inet->cork.base.dst = NULL;
		inet->cork.base.flags &= ~IPCORK_ALLFRAG;
	}
	memset(&inet->cork.fl, 0, sizeof(inet->cork.fl));
}
