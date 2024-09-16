static int sg_get_timeout(struct request_queue *q)
{
	return jiffies_to_clock_t(q->sg_timeout);
}
