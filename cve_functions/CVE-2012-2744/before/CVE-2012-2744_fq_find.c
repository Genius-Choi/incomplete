fq_find(__be32 id, u32 user, struct in6_addr *src, struct in6_addr *dst)
{
	struct inet_frag_queue *q;
	struct ip6_create_arg arg;
	unsigned int hash;

	arg.id = id;
	arg.user = user;
	arg.src = src;
	arg.dst = dst;

	read_lock_bh(&nf_frags.lock);
	hash = inet6_hash_frag(id, src, dst, nf_frags.rnd);

	q = inet_frag_find(&nf_init_frags, &nf_frags, &arg, hash);
	local_bh_enable();
	if (q == NULL)
		goto oom;

	return container_of(q, struct nf_ct_frag6_queue, q);

oom:
	pr_debug("Can't alloc new queue\n");
	return NULL;
}
