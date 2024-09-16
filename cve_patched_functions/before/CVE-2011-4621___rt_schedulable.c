static int __rt_schedulable(struct task_group *tg, u64 period, u64 runtime)
{
	struct rt_schedulable_data data = {
		.tg = tg,
		.rt_period = period,
		.rt_runtime = runtime,
	};

	return walk_tg_tree(tg_schedulable, tg_nop, &data);
}
