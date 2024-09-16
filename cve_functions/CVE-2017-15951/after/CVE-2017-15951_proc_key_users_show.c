static int proc_key_users_show(struct seq_file *m, void *v)
{
	struct rb_node *_p = v;
	struct key_user *user = rb_entry(_p, struct key_user, node);
	unsigned maxkeys = uid_eq(user->uid, GLOBAL_ROOT_UID) ?
		key_quota_root_maxkeys : key_quota_maxkeys;
	unsigned maxbytes = uid_eq(user->uid, GLOBAL_ROOT_UID) ?
		key_quota_root_maxbytes : key_quota_maxbytes;

	seq_printf(m, "%5u: %5d %d/%d %d/%d %d/%d\n",
		   from_kuid_munged(seq_user_ns(m), user->uid),
		   refcount_read(&user->usage),
		   atomic_read(&user->nkeys),
		   atomic_read(&user->nikeys),
		   user->qnkeys,
		   maxkeys,
		   user->qnbytes,
		   maxbytes);

	return 0;
}
