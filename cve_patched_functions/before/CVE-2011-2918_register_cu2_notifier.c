int __ref register_cu2_notifier(struct notifier_block *nb)
{
	return raw_notifier_chain_register(&cu2_chain, nb);
}
