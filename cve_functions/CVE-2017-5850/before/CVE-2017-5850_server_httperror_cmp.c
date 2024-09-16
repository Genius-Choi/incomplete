server_httperror_cmp(const void *a, const void *b)
{
	const struct http_error *ea = a;
	const struct http_error *eb = b;
	return (ea->error_code - eb->error_code);
}
