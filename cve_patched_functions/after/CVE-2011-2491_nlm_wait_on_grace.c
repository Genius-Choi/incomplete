static int nlm_wait_on_grace(wait_queue_head_t *queue)
{
	DEFINE_WAIT(wait);
	int status = -EINTR;

	prepare_to_wait(queue, &wait, TASK_INTERRUPTIBLE);
	if (!signalled ()) {
		schedule_timeout(NLMCLNT_GRACE_WAIT);
		try_to_freeze();
		if (!signalled ())
			status = 0;
	}
	finish_wait(queue, &wait);
	return status;
}
