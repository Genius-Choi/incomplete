static ssize_t qib_write_iter(struct kiocb *iocb, struct iov_iter *from)
{
	struct qib_filedata *fp = iocb->ki_filp->private_data;
	struct qib_ctxtdata *rcd = ctxt_fp(iocb->ki_filp);
	struct qib_user_sdma_queue *pq = fp->pq;

	if (!iter_is_iovec(from) || !from->nr_segs || !pq)
		return -EINVAL;
			 
	return qib_user_sdma_writev(rcd, pq, from->iov, from->nr_segs);
}
