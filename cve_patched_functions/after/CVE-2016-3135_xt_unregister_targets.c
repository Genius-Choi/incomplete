xt_unregister_targets(struct xt_target *target, unsigned int n)
{
	while (n-- > 0)
		xt_unregister_target(&target[n]);
}
