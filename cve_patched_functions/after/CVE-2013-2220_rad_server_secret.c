rad_server_secret(struct rad_handle *h)
{
	if (h->srv >= h->num_servers) {
		generr(h, "No RADIUS servers specified");
		return NULL;
	}

	return (h->servers[h->srv].secret);
}
