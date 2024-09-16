static void ptrace_exit_finish(struct task_struct *parent,
			       struct list_head *dead)
{
	struct task_struct *p, *n;

	BUG_ON(!list_empty(&parent->ptraced));

	list_for_each_entry_safe(p, n, dead, ptrace_entry) {
		list_del_init(&p->ptrace_entry);
		release_task(p);
	}
}
