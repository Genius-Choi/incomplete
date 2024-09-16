static ssize_t hfi1_write_iter(struct kiocb *kiocb, struct iov_iter *from)
{
	struct hfi1_filedata *fd = kiocb->ki_filp->private_data;
	struct hfi1_user_sdma_pkt_q *pq = fd->pq;
	struct hfi1_user_sdma_comp_q *cq = fd->cq;
	int ret = 0, done = 0, reqs = 0;
	unsigned long dim = from->nr_segs;

	if (!cq || !pq) {
		ret = -EIO;
		goto done;
	}

	if (!iter_is_iovec(from) || !dim) {
		ret = -EINVAL;
		goto done;
	}

	hfi1_cdbg(SDMA, "SDMA request from %u:%u (%lu)",
		  fd->uctxt->ctxt, fd->subctxt, dim);

	if (atomic_read(&pq->n_reqs) == pq->n_max_reqs) {
		ret = -ENOSPC;
		goto done;
	}

	while (dim) {
		unsigned long count = 0;

		ret = hfi1_user_sdma_process_request(
			kiocb->ki_filp,	(struct iovec *)(from->iov + done),
			dim, &count);
		if (ret)
			goto done;
		dim -= count;
		done += count;
		reqs++;
	}
done:
	return ret ? ret : reqs;
}
