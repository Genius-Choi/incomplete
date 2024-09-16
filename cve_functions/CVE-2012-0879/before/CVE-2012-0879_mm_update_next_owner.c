void mm_update_next_owner(struct mm_struct *mm)
{
	struct task_struct *c, *g, *p = current;

retry:
	if (!mm_need_new_owner(mm, p))
		return;

	read_lock(&tasklist_lock);
	/*
	 * Search in the children
	 */
	list_for_each_entry(c, &p->children, sibling) {
		if (c->mm == mm)
			goto assign_new_owner;
	}

	/*
	 * Search in the siblings
	 */
	list_for_each_entry(c, &p->real_parent->children, sibling) {
		if (c->mm == mm)
			goto assign_new_owner;
	}

	/*
	 * Search through everything else. We should not get
	 * here often
	 */
	do_each_thread(g, c) {
		if (c->mm == mm)
			goto assign_new_owner;
	} while_each_thread(g, c);

	read_unlock(&tasklist_lock);
	/*
	 * We found no owner yet mm_users > 1: this implies that we are
	 * most likely racing with swapoff (try_to_unuse()) or /proc or
	 * ptrace or page migration (get_task_mm()).  Mark owner as NULL.
	 */
	mm->owner = NULL;
	return;

assign_new_owner:
	BUG_ON(c == p);
	get_task_struct(c);
	/*
	 * The task_lock protects c->mm from changing.
	 * We always want mm->owner->mm == mm
	 */
	task_lock(c);
	/*
	 * Delay read_unlock() till we have the task_lock()
	 * to ensure that c does not slip away underneath us
	 */
	read_unlock(&tasklist_lock);
	if (c->mm != mm) {
		task_unlock(c);
		put_task_struct(c);
		goto retry;
	}
	mm->owner = c;
	task_unlock(c);
	put_task_struct(c);
}
