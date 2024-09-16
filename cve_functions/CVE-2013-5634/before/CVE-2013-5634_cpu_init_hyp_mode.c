static void cpu_init_hyp_mode(void *dummy)
{
	unsigned long long boot_pgd_ptr;
	unsigned long long pgd_ptr;
	unsigned long hyp_stack_ptr;
	unsigned long stack_page;
	unsigned long vector_ptr;

	/* Switch from the HYP stub to our own HYP init vector */
	__hyp_set_vectors(kvm_get_idmap_vector());

	boot_pgd_ptr = (unsigned long long)kvm_mmu_get_boot_httbr();
	pgd_ptr = (unsigned long long)kvm_mmu_get_httbr();
	stack_page = __get_cpu_var(kvm_arm_hyp_stack_page);
	hyp_stack_ptr = stack_page + PAGE_SIZE;
	vector_ptr = (unsigned long)__kvm_hyp_vector;

	__cpu_init_hyp_mode(boot_pgd_ptr, pgd_ptr, hyp_stack_ptr, vector_ptr);
}
