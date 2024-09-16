void inotify_ignored_and_remove_idr(struct fsnotify_mark *fsn_mark,
				    struct fsnotify_group *group)
{
	struct inotify_inode_mark *i_mark;
	struct fsnotify_event *ignored_event, *notify_event;
	struct inotify_event_private_data *event_priv;
	struct fsnotify_event_private_data *fsn_event_priv;
	int ret;

	ignored_event = fsnotify_create_event(NULL, FS_IN_IGNORED, NULL,
					      FSNOTIFY_EVENT_NONE, NULL, 0,
					      GFP_NOFS);
	if (!ignored_event)
		return;

	i_mark = container_of(fsn_mark, struct inotify_inode_mark, fsn_mark);

	event_priv = kmem_cache_alloc(event_priv_cachep, GFP_NOFS);
	if (unlikely(!event_priv))
		goto skip_send_ignore;

	fsn_event_priv = &event_priv->fsnotify_event_priv_data;

	fsn_event_priv->group = group;
	event_priv->wd = i_mark->wd;

	notify_event = fsnotify_add_notify_event(group, ignored_event, fsn_event_priv, NULL);
	if (notify_event) {
		if (IS_ERR(notify_event))
			ret = PTR_ERR(notify_event);
		else
			fsnotify_put_event(notify_event);
		inotify_free_event_priv(fsn_event_priv);
	}

skip_send_ignore:

	/* matches the reference taken when the event was created */
	fsnotify_put_event(ignored_event);

	/* remove this mark from the idr */
	inotify_remove_from_idr(group, i_mark);

	atomic_dec(&group->inotify_data.user->inotify_watches);
}
