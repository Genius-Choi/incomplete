static void mark_umount_candidates(struct mount *mnt)
{
	struct mount *parent = mnt->mnt_parent;
	struct mount *m;

	BUG_ON(parent == mnt);

	for (m = propagation_next(parent, parent); m;
			m = propagation_next(m, parent)) {
		struct mount *child = __lookup_mnt_last(&m->mnt,
						mnt->mnt_mountpoint);
		if (child && (!IS_MNT_LOCKED(child) || IS_MNT_MARKED(m))) {
			SET_MNT_MARK(child);
		}
	}
}
