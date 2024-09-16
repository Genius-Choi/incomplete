bool has_capability(struct task_struct *t, int cap)
{
	return has_ns_capability(t, &init_user_ns, cap);
}
