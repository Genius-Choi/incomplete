static void kgdb_remove_all_hw_break(void)
{
	int i;
	int cpu = raw_smp_processor_id();
	struct perf_event *bp;

	for (i = 0; i < HBP_NUM; i++) {
		if (!breakinfo[i].enabled)
			continue;
		bp = *per_cpu_ptr(breakinfo[i].pev, cpu);
		if (!bp->attr.disabled) {
			arch_uninstall_hw_breakpoint(bp);
			bp->attr.disabled = 1;
			continue;
		}
		if (dbg_is_early)
			early_dr7 &= ~encode_dr7(i, breakinfo[i].len,
						 breakinfo[i].type);
		else if (hw_break_release_slot(i))
			printk(KERN_ERR "KGDB: hw bpt remove failed %lx\n",
			       breakinfo[i].addr);
		breakinfo[i].enabled = 0;
	}
}
