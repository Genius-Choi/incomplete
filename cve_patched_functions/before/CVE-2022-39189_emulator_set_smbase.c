static void emulator_set_smbase(struct x86_emulate_ctxt *ctxt, u64 smbase)
{
	struct kvm_vcpu *vcpu = emul_to_vcpu(ctxt);

	vcpu->arch.smbase = smbase;
}
