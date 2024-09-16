static void remote_function(void *data)
{
	struct remote_function_call *tfc = data;
	struct task_struct *p = tfc->p;

	if (p) {
		tfc->ret = -EAGAIN;
		if (task_cpu(p) != smp_processor_id() || !task_curr(p))
			return;
	}

	tfc->ret = tfc->func(tfc->info);
}
