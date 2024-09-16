int emulator_set_dr(int dr, unsigned long value, struct kvm_vcpu *vcpu)
{

	return __kvm_set_dr(vcpu, dr, value);
}
