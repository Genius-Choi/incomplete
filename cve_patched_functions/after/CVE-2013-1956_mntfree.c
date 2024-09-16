static inline void mntfree(struct mount *mnt)
{
	struct vfsmount *m = &mnt->mnt;
	struct super_block *sb = m->mnt_sb;

	/*
	 * This probably indicates that somebody messed
	 * up a mnt_want/drop_write() pair.  If this
	 * happens, the filesystem was probably unable
	 * to make r/w->r/o transitions.
	 */
	/*
	 * The locking used to deal with mnt_count decrement provides barriers,
	 * so mnt_get_writers() below is safe.
	 */
	WARN_ON(mnt_get_writers(mnt));
	fsnotify_vfsmount_delete(m);
	dput(m->mnt_root);
	free_vfsmnt(mnt);
	deactivate_super(sb);
}
