svc_rqst_alloc(struct svc_serv *serv, struct svc_pool *pool, int node)
{
	struct svc_rqst	*rqstp;

	rqstp = kzalloc_node(sizeof(*rqstp), GFP_KERNEL, node);
	if (!rqstp)
		return rqstp;

	__set_bit(RQ_BUSY, &rqstp->rq_flags);
	spin_lock_init(&rqstp->rq_lock);
	rqstp->rq_server = serv;
	rqstp->rq_pool = pool;

	rqstp->rq_argp = kmalloc_node(serv->sv_xdrsize, GFP_KERNEL, node);
	if (!rqstp->rq_argp)
		goto out_enomem;

	rqstp->rq_resp = kmalloc_node(serv->sv_xdrsize, GFP_KERNEL, node);
	if (!rqstp->rq_resp)
		goto out_enomem;

	if (!svc_init_buffer(rqstp, serv->sv_max_mesg, node))
		goto out_enomem;

	return rqstp;
out_enomem:
	svc_rqst_free(rqstp);
	return NULL;
}
