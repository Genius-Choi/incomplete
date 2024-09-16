unsigned long perf_instruction_pointer(struct pt_regs *regs)
{
	unsigned long ip;

	if (perf_guest_cbs && perf_guest_cbs->is_in_guest())
		ip = perf_guest_cbs->get_guest_ip();
	else
		ip = instruction_pointer(regs);

	return ip;
}
