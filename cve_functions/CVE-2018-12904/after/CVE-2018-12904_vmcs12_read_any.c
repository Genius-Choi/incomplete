static inline int vmcs12_read_any(struct kvm_vcpu *vcpu,
				  unsigned long field, u64 *ret)
{
	short offset = vmcs_field_to_offset(field);
	char *p;

	if (offset < 0)
		return offset;

	p = ((char *)(get_vmcs12(vcpu))) + offset;

	switch (vmcs_field_width(field)) {
	case VMCS_FIELD_WIDTH_NATURAL_WIDTH:
		*ret = *((natural_width *)p);
		return 0;
	case VMCS_FIELD_WIDTH_U16:
		*ret = *((u16 *)p);
		return 0;
	case VMCS_FIELD_WIDTH_U32:
		*ret = *((u32 *)p);
		return 0;
	case VMCS_FIELD_WIDTH_U64:
		*ret = *((u64 *)p);
		return 0;
	default:
		WARN_ON(1);
		return -ENOENT;
	}
}
