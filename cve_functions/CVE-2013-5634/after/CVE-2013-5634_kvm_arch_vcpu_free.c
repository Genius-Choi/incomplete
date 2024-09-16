void kvm_arch_vcpu_free(struct kvm_vcpu *vcpu)
{
	kvm_mmu_free_memory_caches(vcpu);
	kvm_timer_vcpu_terminate(vcpu);
	kmem_cache_free(kvm_vcpu_cache, vcpu);
}
