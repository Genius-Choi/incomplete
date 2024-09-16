static void __net_exit bond_net_exit(struct net *net)
{
	struct bond_net *bn = net_generic(net, bond_net_id);

	bond_destroy_proc_dir(bn);
}
