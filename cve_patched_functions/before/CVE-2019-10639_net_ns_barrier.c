void net_ns_barrier(void)
{
	down_write(&pernet_ops_rwsem);
	up_write(&pernet_ops_rwsem);
}
