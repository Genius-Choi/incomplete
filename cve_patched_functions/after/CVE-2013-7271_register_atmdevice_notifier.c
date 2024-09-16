int register_atmdevice_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&atm_dev_notify_chain, nb);
}
