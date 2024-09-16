static void sctp_v6_get_saddr(struct sctp_sock *sk,
			      struct sctp_transport *t,
			      struct flowi *fl)
{
	struct flowi6 *fl6 = &fl->u.ip6;
	union sctp_addr *saddr = &t->saddr;

	pr_debug("%s: asoc:%p dst:%p\n", __func__, t->asoc, t->dst);

	if (t->dst) {
		saddr->v6.sin6_family = AF_INET6;
		saddr->v6.sin6_addr = fl6->saddr;
	}
}
