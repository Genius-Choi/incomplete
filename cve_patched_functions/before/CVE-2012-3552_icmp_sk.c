static struct sock *icmp_sk(struct net *net)
{
	return net->ipv4.icmp_sk[smp_processor_id()];
}
