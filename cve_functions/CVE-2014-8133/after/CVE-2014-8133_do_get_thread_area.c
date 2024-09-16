int do_get_thread_area(struct task_struct *p, int idx,
		       struct user_desc __user *u_info)
{
	struct user_desc info;

	if (idx == -1 && get_user(idx, &u_info->entry_number))
		return -EFAULT;

	if (idx < GDT_ENTRY_TLS_MIN || idx > GDT_ENTRY_TLS_MAX)
		return -EINVAL;

	fill_user_desc(&info, idx,
		       &p->thread.tls_array[idx - GDT_ENTRY_TLS_MIN]);

	if (copy_to_user(u_info, &info, sizeof(info)))
		return -EFAULT;
	return 0;
}
