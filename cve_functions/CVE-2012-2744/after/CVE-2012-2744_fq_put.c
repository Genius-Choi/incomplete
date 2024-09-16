static __inline__ void fq_put(struct nf_ct_frag6_queue *fq)
{
	inet_frag_put(&fq->q, &nf_frags);
}
