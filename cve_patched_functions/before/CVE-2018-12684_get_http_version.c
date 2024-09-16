get_http_version(const struct mg_connection *conn)
{
	if (!conn) {
		return NULL;
	}

	if (conn->connection_type == CONNECTION_TYPE_REQUEST) {
		return conn->request_info.http_version;
	}
	if (conn->connection_type == CONNECTION_TYPE_RESPONSE) {
		return conn->response_info.http_version;
	}
	return NULL;
}
