static int update_counters(struct net *net, const void __user *user,
			    unsigned int len)
{
	struct ebt_replace hlp;

	if (copy_from_user(&hlp, user, sizeof(hlp)))
		return -EFAULT;

	if (len != sizeof(hlp) + hlp.num_counters * sizeof(struct ebt_counter))
		return -EINVAL;

	return do_update_counters(net, hlp.name, hlp.counters,
				hlp.num_counters, user, len);
}
