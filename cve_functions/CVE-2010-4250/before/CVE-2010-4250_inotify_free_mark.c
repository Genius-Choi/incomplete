static void inotify_free_mark(struct fsnotify_mark *fsn_mark)
{
	struct inotify_inode_mark *i_mark;

	i_mark = container_of(fsn_mark, struct inotify_inode_mark, fsn_mark);

	kmem_cache_free(inotify_inode_mark_cachep, i_mark);
}
