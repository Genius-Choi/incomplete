static int qib_sdma_get_complete(struct qib_pportdata *ppd,
				 struct qib_user_sdma_queue *pq,
				 u32 __user *completep)
{
	u32 val;
	int err;

	if (!pq)
		return -EINVAL;

	err = qib_user_sdma_make_progress(ppd, pq);
	if (err < 0)
		return err;

	val = qib_user_sdma_complete_counter(pq);
	if (put_user(val, completep))
		return -EFAULT;

	return 0;
}
