__be32 nfsd_splice_read(struct svc_rqst *rqstp,
		     struct file *file, loff_t offset, unsigned long *count)
{
	struct splice_desc sd = {
		.len		= 0,
		.total_len	= *count,
		.pos		= offset,
		.u.data		= rqstp,
	};
	int host_err;

	rqstp->rq_next_page = rqstp->rq_respages + 1;
	host_err = splice_direct_to_actor(file, &sd, nfsd_direct_splice_actor);
	return nfsd_finish_read(file, count, host_err);
}
