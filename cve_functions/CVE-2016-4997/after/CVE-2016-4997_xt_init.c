static int __init xt_init(void)
{
	unsigned int i;
	int rv;

	for_each_possible_cpu(i) {
		seqcount_init(&per_cpu(xt_recseq, i));
	}

	xt = kmalloc(sizeof(struct xt_af) * NFPROTO_NUMPROTO, GFP_KERNEL);
	if (!xt)
		return -ENOMEM;

	for (i = 0; i < NFPROTO_NUMPROTO; i++) {
		mutex_init(&xt[i].mutex);
#ifdef CONFIG_COMPAT
		mutex_init(&xt[i].compat_mutex);
		xt[i].compat_tab = NULL;
#endif
		INIT_LIST_HEAD(&xt[i].target);
		INIT_LIST_HEAD(&xt[i].match);
	}
	rv = register_pernet_subsys(&xt_net_ops);
	if (rv < 0)
		kfree(xt);
	return rv;
}
