static int ib_ucm_path_get(struct ib_sa_path_rec **path, u64 src)
{
	struct ib_user_path_rec upath;
	struct ib_sa_path_rec  *sa_path;

	*path = NULL;

	if (!src)
		return 0;

	sa_path = kmalloc(sizeof(*sa_path), GFP_KERNEL);
	if (!sa_path)
		return -ENOMEM;

	if (copy_from_user(&upath, (void __user *)(unsigned long)src,
			   sizeof(upath))) {

		kfree(sa_path);
		return -EFAULT;
	}

	ib_copy_path_rec_from_user(sa_path, &upath);
	*path = sa_path;
	return 0;
}
