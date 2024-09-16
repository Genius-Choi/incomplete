static int nested_vmx_check_msr_switch(struct kvm_vcpu *vcpu,
				       unsigned long count_field,
				       unsigned long addr_field)
{
	int maxphyaddr;
	u64 count, addr;

	if (vmcs12_read_any(vcpu, count_field, &count) ||
	    vmcs12_read_any(vcpu, addr_field, &addr)) {
		WARN_ON(1);
		return -EINVAL;
	}
	if (count == 0)
		return 0;
	maxphyaddr = cpuid_maxphyaddr(vcpu);
	if (!IS_ALIGNED(addr, 16) || addr >> maxphyaddr ||
	    (addr + count * sizeof(struct vmx_msr_entry) - 1) >> maxphyaddr) {
		pr_warn_ratelimited(
			"nVMX: invalid MSR switch (0x%lx, %d, %llu, 0x%08llx)",
			addr_field, maxphyaddr, count, addr);
		return -EINVAL;
	}
	return 0;
}
