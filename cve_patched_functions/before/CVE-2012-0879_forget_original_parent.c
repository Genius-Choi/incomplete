static void forget_original_parent(struct task_struct *father)
{
	struct task_struct *p, *n, *reaper;
	LIST_HEAD(dead_children);

	exit_ptrace(father);

	write_lock_irq(&tasklist_lock);
	reaper = find_new_reaper(father);

	list_for_each_entry_safe(p, n, &father->children, sibling) {
		p->real_parent = reaper;
		if (p->parent == father) {
			BUG_ON(task_ptrace(p));
			p->parent = p->real_parent;
		}
		reparent_thread(father, p, &dead_children);
	}
	write_unlock_irq(&tasklist_lock);

	BUG_ON(!list_empty(&father->children));

	list_for_each_entry_safe(p, n, &dead_children, sibling) {
		list_del_init(&p->sibling);
		release_task(p);
	}
}
