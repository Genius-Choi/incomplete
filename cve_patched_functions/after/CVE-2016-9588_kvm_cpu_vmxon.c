static void kvm_cpu_vmxon(u64 addr)
{
	intel_pt_handle_vmx(1);

	asm volatile (ASM_VMX_VMXON_RAX
			: : "a"(&addr), "m"(addr)
			: "memory", "cc");
}
