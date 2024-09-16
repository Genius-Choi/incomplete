static void migrate_live_tasks(int src_cpu)
{
	struct task_struct *p, *t;

	read_lock(&tasklist_lock);

	do_each_thread(t, p) {
		if (p == current)
			continue;

		if (task_cpu(p) == src_cpu)
			move_task_off_dead_cpu(src_cpu, p);
	} while_each_thread(t, p);

	read_unlock(&tasklist_lock);
}
