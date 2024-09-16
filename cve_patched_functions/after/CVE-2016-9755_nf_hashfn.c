static unsigned int nf_hashfn(const struct inet_frag_queue *q)
{
	const struct frag_queue *nq;

	nq = container_of(q, struct frag_queue, q);
	return nf_hash_frag(nq->id, &nq->saddr, &nq->daddr);
}
