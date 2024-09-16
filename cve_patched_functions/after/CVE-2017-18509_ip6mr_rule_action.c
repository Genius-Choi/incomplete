static int ip6mr_rule_action(struct fib_rule *rule, struct flowi *flp,
			     int flags, struct fib_lookup_arg *arg)
{
	struct ip6mr_result *res = arg->result;
	struct mr6_table *mrt;

	switch (rule->action) {
	case FR_ACT_TO_TBL:
		break;
	case FR_ACT_UNREACHABLE:
		return -ENETUNREACH;
	case FR_ACT_PROHIBIT:
		return -EACCES;
	case FR_ACT_BLACKHOLE:
	default:
		return -EINVAL;
	}

	mrt = ip6mr_get_table(rule->fr_net, rule->table);
	if (!mrt)
		return -EAGAIN;
	res->mrt = mrt;
	return 0;
}
