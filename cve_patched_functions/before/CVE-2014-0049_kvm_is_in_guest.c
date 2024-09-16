int kvm_is_in_guest(void)
{
	return __this_cpu_read(current_vcpu) != NULL;
}
