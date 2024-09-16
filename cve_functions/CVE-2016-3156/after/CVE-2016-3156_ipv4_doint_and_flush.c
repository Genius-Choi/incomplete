static int ipv4_doint_and_flush(struct ctl_table *ctl, int write,
				void __user *buffer,
				size_t *lenp, loff_t *ppos)
{
	int *valp = ctl->data;
	int val = *valp;
	int ret = proc_dointvec(ctl, write, buffer, lenp, ppos);
	struct net *net = ctl->extra2;

	if (write && *valp != val)
		rt_cache_flush(net);

	return ret;
}
