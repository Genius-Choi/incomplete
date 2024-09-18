static __net_init int pppol2tp_init_net(struct net *net)
{
	struct proc_dir_entry *pde;
	int err = 0;

	pde = proc_create("pppol2tp", S_IRUGO, net->proc_net,
			  &pppol2tp_proc_fops);
	if (!pde) {
		err = -ENOMEM;
		goto out;
	}

out:
	return err;
}
