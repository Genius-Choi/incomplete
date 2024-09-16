int netlink_register_notifier(struct notifier_block *nb)
{
	return atomic_notifier_chain_register(&netlink_chain, nb);
}
