static unsigned int inotify_poll(struct file *file, poll_table *wait)
{
	struct fsnotify_group *group = file->private_data;
	int ret = 0;

	poll_wait(file, &group->notification_waitq, wait);
	mutex_lock(&group->notification_mutex);
	if (!fsnotify_notify_queue_is_empty(group))
		ret = POLLIN | POLLRDNORM;
	mutex_unlock(&group->notification_mutex);

	return ret;
}
