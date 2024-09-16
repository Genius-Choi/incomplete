int ip_frag_nqueues(struct net *net)
{
	return net->ipv4.frags.nqueues;
}
