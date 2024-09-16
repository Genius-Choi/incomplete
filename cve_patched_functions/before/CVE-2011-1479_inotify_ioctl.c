static long inotify_ioctl(struct file *file, unsigned int cmd,
			  unsigned long arg)
{
	struct fsnotify_group *group;
	struct fsnotify_event_holder *holder;
	struct fsnotify_event *event;
	void __user *p;
	int ret = -ENOTTY;
	size_t send_len = 0;

	group = file->private_data;
	p = (void __user *) arg;

	pr_debug("%s: group=%p cmd=%u\n", __func__, group, cmd);

	switch (cmd) {
	case FIONREAD:
		mutex_lock(&group->notification_mutex);
		list_for_each_entry(holder, &group->notification_list, event_list) {
			event = holder->event;
			send_len += sizeof(struct inotify_event);
			if (event->name_len)
				send_len += roundup(event->name_len + 1,
						sizeof(struct inotify_event));
		}
		mutex_unlock(&group->notification_mutex);
		ret = put_user(send_len, (int __user *) p);
		break;
	}

	return ret;
}
