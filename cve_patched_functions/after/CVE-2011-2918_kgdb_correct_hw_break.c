static void kgdb_correct_hw_break(void)
{
	int breakno;

	for (breakno = 0; breakno < HBP_NUM; breakno++) {
		struct perf_event *bp;
		struct arch_hw_breakpoint *info;
		int val;
		int cpu = raw_smp_processor_id();
		if (!breakinfo[breakno].enabled)
			continue;
		if (dbg_is_early) {
			set_debugreg(breakinfo[breakno].addr, breakno);
			early_dr7 |= encode_dr7(breakno,
						breakinfo[breakno].len,
						breakinfo[breakno].type);
			set_debugreg(early_dr7, 7);
			continue;
		}
		bp = *per_cpu_ptr(breakinfo[breakno].pev, cpu);
		info = counter_arch_bp(bp);
		if (bp->attr.disabled != 1)
			continue;
		bp->attr.bp_addr = breakinfo[breakno].addr;
		bp->attr.bp_len = breakinfo[breakno].len;
		bp->attr.bp_type = breakinfo[breakno].type;
		info->address = breakinfo[breakno].addr;
		info->len = breakinfo[breakno].len;
		info->type = breakinfo[breakno].type;
		val = arch_install_hw_breakpoint(bp);
		if (!val)
			bp->attr.disabled = 0;
	}
	if (!dbg_is_early)
		hw_breakpoint_restore();
}
