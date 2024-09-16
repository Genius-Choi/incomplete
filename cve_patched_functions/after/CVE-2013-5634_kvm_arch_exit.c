void kvm_arch_exit(void)
{
	kvm_perf_teardown();
}
