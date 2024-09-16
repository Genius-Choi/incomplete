void kvm_arch_commit_memory_region(struct kvm *kvm,
				struct kvm_userspace_memory_region *mem,
				struct kvm_memory_slot old,
				int user_alloc)
{

	int npages = mem->memory_size >> PAGE_SHIFT;

	if (!user_alloc && !old.user_alloc && old.rmap && !npages) {
		int ret;

		down_write(&current->mm->mmap_sem);
		ret = do_munmap(current->mm, old.userspace_addr,
				old.npages * PAGE_SIZE);
		up_write(&current->mm->mmap_sem);
		if (ret < 0)
			printk(KERN_WARNING
			       "kvm_vm_ioctl_set_memory_region: "
			       "failed to munmap memory\n");
	}

	spin_lock(&kvm->mmu_lock);
	if (!kvm->arch.n_requested_mmu_pages) {
		unsigned int nr_mmu_pages = kvm_mmu_calculate_mmu_pages(kvm);
		kvm_mmu_change_mmu_pages(kvm, nr_mmu_pages);
	}

	kvm_mmu_slot_remove_write_access(kvm, mem->slot);
	spin_unlock(&kvm->mmu_lock);
}
