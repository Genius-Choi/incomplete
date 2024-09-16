static bool inotify_should_send_event(struct fsnotify_group *group, struct inode *inode,
				      struct fsnotify_mark *inode_mark,
				      struct fsnotify_mark *vfsmount_mark,
				      __u32 mask, void *data, int data_type)
{
	if ((inode_mark->mask & FS_EXCL_UNLINK) &&
	    (data_type == FSNOTIFY_EVENT_PATH)) {
		struct path *path = data;

		if (d_unlinked(path->dentry))
			return false;
	}

	return true;
}
