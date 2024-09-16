static void check_kvm_target_cpu(void *ret)
{
	*(int *)ret = kvm_target_cpu();
}
