nfsd_vfs_read(struct svc_rqst *rqstp, struct file *file,
	      loff_t offset, struct kvec *vec, int vlen, unsigned long *count)
{
	if (file->f_op->splice_read && test_bit(RQ_SPLICE_OK, &rqstp->rq_flags))
		return nfsd_splice_read(rqstp, file, offset, count);
	else
		return nfsd_readv(file, offset, vec, vlen, count);
}
