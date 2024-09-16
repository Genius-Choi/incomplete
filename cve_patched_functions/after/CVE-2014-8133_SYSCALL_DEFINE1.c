SYSCALL_DEFINE1(get_thread_area, struct user_desc __user *, u_info)
{
	return do_get_thread_area(current, -1, u_info);
}
