bool has_ns_capability_noaudit(struct task_struct *t,
			       struct user_namespace *ns, int cap)
{
	int ret;

	rcu_read_lock();
	ret = security_capable_noaudit(__task_cred(t), ns, cap);
	rcu_read_unlock();

	return (ret == 0);
}
