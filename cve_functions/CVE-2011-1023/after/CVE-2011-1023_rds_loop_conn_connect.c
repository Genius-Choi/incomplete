static int rds_loop_conn_connect(struct rds_connection *conn)
{
	rds_connect_complete(conn);
	return 0;
}
