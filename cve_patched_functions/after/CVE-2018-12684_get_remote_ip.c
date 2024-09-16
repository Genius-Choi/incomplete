get_remote_ip(const struct mg_connection *conn)
{
	if (!conn) {
		return 0;
	}
	return ntohl(*(const uint32_t *)&conn->client.rsa.sin.sin_addr);
}
