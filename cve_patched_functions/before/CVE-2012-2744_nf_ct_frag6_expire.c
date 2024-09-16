static void nf_ct_frag6_expire(unsigned long data)
{
	struct nf_ct_frag6_queue *fq;

	fq = container_of((struct inet_frag_queue *)data,
			struct nf_ct_frag6_queue, q);

	spin_lock(&fq->q.lock);

	if (fq->q.last_in & INET_FRAG_COMPLETE)
		goto out;

	fq_kill(fq);

out:
	spin_unlock(&fq->q.lock);
	fq_put(fq);
}
