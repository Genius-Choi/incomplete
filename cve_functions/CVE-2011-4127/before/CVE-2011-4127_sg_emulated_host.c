static int sg_emulated_host(struct request_queue *q, int __user *p)
{
	return put_user(1, p);
}
