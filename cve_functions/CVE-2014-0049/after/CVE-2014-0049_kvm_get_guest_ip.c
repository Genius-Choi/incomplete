static unsigned long kvm_get_guest_ip(void)
{
	unsigned long ip = 0;

	if (__this_cpu_read(current_vcpu))
		ip = kvm_rip_read(__this_cpu_read(current_vcpu));

	return ip;
}
