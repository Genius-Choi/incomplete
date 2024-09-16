static void nested_vmx_cr_fixed1_bits_update(struct kvm_vcpu *vcpu)
{
	struct vcpu_vmx *vmx = to_vmx(vcpu);
	struct kvm_cpuid_entry2 *entry;

	vmx->nested.msrs.cr0_fixed1 = 0xffffffff;
	vmx->nested.msrs.cr4_fixed1 = X86_CR4_PCE;

#define cr4_fixed1_update(_cr4_mask, _reg, _cpuid_mask) do {		\
	if (entry && (entry->_reg & (_cpuid_mask)))			\
		vmx->nested.msrs.cr4_fixed1 |= (_cr4_mask);	\
} while (0)

	entry = kvm_find_cpuid_entry(vcpu, 0x1, 0);
	cr4_fixed1_update(X86_CR4_VME,        edx, bit(X86_FEATURE_VME));
	cr4_fixed1_update(X86_CR4_PVI,        edx, bit(X86_FEATURE_VME));
	cr4_fixed1_update(X86_CR4_TSD,        edx, bit(X86_FEATURE_TSC));
	cr4_fixed1_update(X86_CR4_DE,         edx, bit(X86_FEATURE_DE));
	cr4_fixed1_update(X86_CR4_PSE,        edx, bit(X86_FEATURE_PSE));
	cr4_fixed1_update(X86_CR4_PAE,        edx, bit(X86_FEATURE_PAE));
	cr4_fixed1_update(X86_CR4_MCE,        edx, bit(X86_FEATURE_MCE));
	cr4_fixed1_update(X86_CR4_PGE,        edx, bit(X86_FEATURE_PGE));
	cr4_fixed1_update(X86_CR4_OSFXSR,     edx, bit(X86_FEATURE_FXSR));
	cr4_fixed1_update(X86_CR4_OSXMMEXCPT, edx, bit(X86_FEATURE_XMM));
	cr4_fixed1_update(X86_CR4_VMXE,       ecx, bit(X86_FEATURE_VMX));
	cr4_fixed1_update(X86_CR4_SMXE,       ecx, bit(X86_FEATURE_SMX));
	cr4_fixed1_update(X86_CR4_PCIDE,      ecx, bit(X86_FEATURE_PCID));
	cr4_fixed1_update(X86_CR4_OSXSAVE,    ecx, bit(X86_FEATURE_XSAVE));

	entry = kvm_find_cpuid_entry(vcpu, 0x7, 0);
	cr4_fixed1_update(X86_CR4_FSGSBASE,   ebx, bit(X86_FEATURE_FSGSBASE));
	cr4_fixed1_update(X86_CR4_SMEP,       ebx, bit(X86_FEATURE_SMEP));
	cr4_fixed1_update(X86_CR4_SMAP,       ebx, bit(X86_FEATURE_SMAP));
	cr4_fixed1_update(X86_CR4_PKE,        ecx, bit(X86_FEATURE_PKU));
	cr4_fixed1_update(X86_CR4_UMIP,       ecx, bit(X86_FEATURE_UMIP));

#undef cr4_fixed1_update
}
