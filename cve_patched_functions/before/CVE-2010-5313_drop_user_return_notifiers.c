static void drop_user_return_notifiers(void *ignore)
{
	struct kvm_shared_msrs *smsr = &__get_cpu_var(shared_msrs);

	if (smsr->registered)
		kvm_on_user_return(&smsr->urn);
}
