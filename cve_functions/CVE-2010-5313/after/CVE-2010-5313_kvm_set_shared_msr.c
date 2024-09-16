void kvm_set_shared_msr(unsigned slot, u64 value, u64 mask)
{
	struct kvm_shared_msrs *smsr = &__get_cpu_var(shared_msrs);

	if (((value ^ smsr->values[slot].curr) & mask) == 0)
		return;
	smsr->values[slot].curr = value;
	wrmsrl(shared_msrs_global.msrs[slot], value);
	if (!smsr->registered) {
		smsr->urn.on_user_return = kvm_on_user_return;
		user_return_notifier_register(&smsr->urn);
		smsr->registered = true;
	}
}
