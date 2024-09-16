void __detach_mounts(struct dentry *dentry)
{
	struct mountpoint *mp;
	struct mount *mnt;

	namespace_lock();
	mp = lookup_mountpoint(dentry);
	if (IS_ERR_OR_NULL(mp))
		goto out_unlock;

	lock_mount_hash();
	event++;
	while (!hlist_empty(&mp->m_list)) {
		mnt = hlist_entry(mp->m_list.first, struct mount, mnt_mp_list);
		if (mnt->mnt.mnt_flags & MNT_UMOUNT) {
			hlist_add_head(&mnt->mnt_umount.s_list, &unmounted);
			umount_mnt(mnt);
		}
		else umount_tree(mnt, UMOUNT_CONNECTED);
	}
	unlock_mount_hash();
	put_mountpoint(mp);
out_unlock:
	namespace_unlock();
}
