static bool rds_tcp_is_unloading(struct rds_connection *conn)
{
	return atomic_read(&rds_tcp_unloading) != 0;
}
