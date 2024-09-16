void native_flush_tlb_others(const struct cpumask *cpumask,
				 struct mm_struct *mm, unsigned long start,
				 unsigned long end)
{
	struct flush_tlb_info info;
	info.flush_mm = mm;
	info.flush_start = start;
	info.flush_end = end;

	count_vm_tlb_event(NR_TLB_REMOTE_FLUSH);
	trace_tlb_flush(TLB_REMOTE_SEND_IPI, end - start);
	if (is_uv_system()) {
		unsigned int cpu;

		cpu = smp_processor_id();
		cpumask = uv_flush_tlb_others(cpumask, mm, start, end, cpu);
		if (cpumask)
			smp_call_function_many(cpumask, flush_tlb_func,
								&info, 1);
		return;
	}
	smp_call_function_many(cpumask, flush_tlb_func, &info, 1);
}
