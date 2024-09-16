static void unhash_mnt(struct mount *mnt)
{
	mnt->mnt_parent = mnt;
	mnt->mnt_mountpoint = mnt->mnt.mnt_root;
	list_del_init(&mnt->mnt_child);
	hlist_del_init_rcu(&mnt->mnt_hash);
	hlist_del_init(&mnt->mnt_mp_list);
	put_mountpoint(mnt->mnt_mp);
	mnt->mnt_mp = NULL;
}
