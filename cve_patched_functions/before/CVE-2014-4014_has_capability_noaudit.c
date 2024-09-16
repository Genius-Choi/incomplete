bool has_capability_noaudit(struct task_struct *t, int cap)
{
	return has_ns_capability_noaudit(t, &init_user_ns, cap);
}
