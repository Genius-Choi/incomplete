static int sg_get_reserved_size(struct request_queue *q, int __user *p)
{
	unsigned val = min(q->sg_reserved_size, queue_max_sectors(q) << 9);

	return put_user(val, p);
}
