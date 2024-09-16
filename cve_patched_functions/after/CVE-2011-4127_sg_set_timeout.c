static int sg_set_timeout(struct request_queue *q, int __user *p)
{
	int timeout, err = get_user(timeout, p);

	if (!err)
		q->sg_timeout = clock_t_to_jiffies(timeout);

	return err;
}
