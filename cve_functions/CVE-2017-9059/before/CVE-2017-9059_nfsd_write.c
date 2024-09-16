nfsd_write(struct svc_rqst *rqstp, struct svc_fh *fhp, loff_t offset,
	   struct kvec *vec, int vlen, unsigned long *cnt, int stable)
{
	struct file *file = NULL;
	__be32 err = 0;

	trace_write_start(rqstp, fhp, offset, vlen);

	err = nfsd_open(rqstp, fhp, S_IFREG, NFSD_MAY_WRITE, &file);
	if (err)
		goto out;

	trace_write_opened(rqstp, fhp, offset, vlen);
	err = nfsd_vfs_write(rqstp, fhp, file, offset, vec, vlen, cnt, stable);
	trace_write_io_done(rqstp, fhp, offset, vlen);
	fput(file);
out:
	trace_write_done(rqstp, fhp, offset, vlen);
	return err;
}
