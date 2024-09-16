static int qib_sdma_get_inflight(struct qib_user_sdma_queue *pq,
				 u32 __user *inflightp)
{
	const u32 val = qib_user_sdma_inflight_counter(pq);

	if (put_user(val, inflightp))
		return -EFAULT;

	return 0;
}
