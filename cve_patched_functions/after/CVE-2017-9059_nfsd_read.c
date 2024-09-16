__be32 nfsd_read(struct svc_rqst *rqstp, struct svc_fh *fhp,
	loff_t offset, struct kvec *vec, int vlen, unsigned long *count)
{
	struct file *file;
	struct raparms	*ra;
	__be32 err;

	trace_read_start(rqstp, fhp, offset, vlen);
	err = nfsd_open(rqstp, fhp, S_IFREG, NFSD_MAY_READ, &file);
	if (err)
		return err;

	ra = nfsd_init_raparms(file);

	trace_read_opened(rqstp, fhp, offset, vlen);
	err = nfsd_vfs_read(rqstp, file, offset, vec, vlen, count);
	trace_read_io_done(rqstp, fhp, offset, vlen);

	if (ra)
		nfsd_put_raparams(file, ra);
	fput(file);

	trace_read_done(rqstp, fhp, offset, vlen);

	return err;
}
