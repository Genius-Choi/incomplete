void arch_show_smap(struct seq_file *m, struct vm_area_struct *vma)
{
	if (!boot_cpu_has(X86_FEATURE_OSPKE))
		return;

	seq_printf(m, "ProtectionKey:  %8u\n", vma_pkey(vma));
}
