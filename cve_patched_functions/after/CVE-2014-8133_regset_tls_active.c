int regset_tls_active(struct task_struct *target,
		      const struct user_regset *regset)
{
	struct thread_struct *t = &target->thread;
	int n = GDT_ENTRY_TLS_ENTRIES;
	while (n > 0 && desc_empty(&t->tls_array[n - 1]))
		--n;
	return n;
}
