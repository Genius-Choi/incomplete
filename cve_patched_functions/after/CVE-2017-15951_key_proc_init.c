static int __init key_proc_init(void)
{
	struct proc_dir_entry *p;

	p = proc_create("keys", 0, NULL, &proc_keys_fops);
	if (!p)
		panic("Cannot create /proc/keys\n");

	p = proc_create("key-users", 0, NULL, &proc_key_users_fops);
	if (!p)
		panic("Cannot create /proc/key-users\n");

	return 0;
}
