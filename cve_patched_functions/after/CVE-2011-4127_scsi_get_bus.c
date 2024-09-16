static int scsi_get_bus(struct request_queue *q, int __user *p)
{
	return put_user(0, p);
}
