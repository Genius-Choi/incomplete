static inline int apic_lvt_vector(struct kvm_lapic *apic, int lvt_type)
{
	return kvm_apic_get_reg(apic, lvt_type) & APIC_VECTOR_MASK;
}
