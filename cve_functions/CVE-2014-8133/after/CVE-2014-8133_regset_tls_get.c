int regset_tls_get(struct task_struct *target, const struct user_regset *regset,
		   unsigned int pos, unsigned int count,
		   void *kbuf, void __user *ubuf)
{
	const struct desc_struct *tls;

	if (pos >= GDT_ENTRY_TLS_ENTRIES * sizeof(struct user_desc) ||
	    (pos % sizeof(struct user_desc)) != 0 ||
	    (count % sizeof(struct user_desc)) != 0)
		return -EINVAL;

	pos /= sizeof(struct user_desc);
	count /= sizeof(struct user_desc);

	tls = &target->thread.tls_array[pos];

	if (kbuf) {
		struct user_desc *info = kbuf;
		while (count-- > 0)
			fill_user_desc(info++, GDT_ENTRY_TLS_MIN + pos++,
				       tls++);
	} else {
		struct user_desc __user *u_info = ubuf;
		while (count-- > 0) {
			struct user_desc info;
			fill_user_desc(&info, GDT_ENTRY_TLS_MIN + pos++, tls++);
			if (__copy_to_user(u_info++, &info, sizeof(info)))
				return -EFAULT;
		}
	}

	return 0;
}
