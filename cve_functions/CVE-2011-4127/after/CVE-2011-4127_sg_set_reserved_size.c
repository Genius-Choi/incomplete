static int sg_set_reserved_size(struct request_queue *q, int __user *p)
{
	int size, err = get_user(size, p);

	if (err)
		return err;

	if (size < 0)
		return -EINVAL;
	if (size > (queue_max_sectors(q) << 9))
		size = queue_max_sectors(q) << 9;

	q->sg_reserved_size = size;
	return 0;
}
