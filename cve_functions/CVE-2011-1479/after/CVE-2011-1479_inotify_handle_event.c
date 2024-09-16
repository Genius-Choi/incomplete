static int inotify_handle_event(struct fsnotify_group *group,
				struct fsnotify_mark *inode_mark,
				struct fsnotify_mark *vfsmount_mark,
				struct fsnotify_event *event)
{
	struct inotify_inode_mark *i_mark;
	struct inode *to_tell;
	struct inotify_event_private_data *event_priv;
	struct fsnotify_event_private_data *fsn_event_priv;
	struct fsnotify_event *added_event;
	int wd, ret = 0;

	BUG_ON(vfsmount_mark);

	pr_debug("%s: group=%p event=%p to_tell=%p mask=%x\n", __func__, group,
		 event, event->to_tell, event->mask);

	to_tell = event->to_tell;

	i_mark = container_of(inode_mark, struct inotify_inode_mark,
			      fsn_mark);
	wd = i_mark->wd;

	event_priv = kmem_cache_alloc(event_priv_cachep, GFP_KERNEL);
	if (unlikely(!event_priv))
		return -ENOMEM;

	fsn_event_priv = &event_priv->fsnotify_event_priv_data;

	fsn_event_priv->group = group;
	event_priv->wd = wd;

	added_event = fsnotify_add_notify_event(group, event, fsn_event_priv, inotify_merge);
	if (added_event) {
		inotify_free_event_priv(fsn_event_priv);
		if (!IS_ERR(added_event))
			fsnotify_put_event(added_event);
		else
			ret = PTR_ERR(added_event);
	}

	if (inode_mark->mask & IN_ONESHOT)
		fsnotify_destroy_mark(inode_mark);

	return ret;
}
