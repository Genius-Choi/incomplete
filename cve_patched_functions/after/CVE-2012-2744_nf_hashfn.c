static unsigned int nf_hashfn(struct inet_frag_queue *q)
{
	const struct nf_ct_frag6_queue *nq;

	nq = container_of(q, struct nf_ct_frag6_queue, q);
	return inet6_hash_frag(nq->id, &nq->saddr, &nq->daddr, nf_frags.rnd);
}
