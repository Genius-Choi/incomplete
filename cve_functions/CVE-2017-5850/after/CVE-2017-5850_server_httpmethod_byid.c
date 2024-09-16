server_httpmethod_byid(unsigned int id)
{
	const char	*name = "<UNKNOWN>";
	int		 i;

	for (i = 0; http_methods[i].method_name != NULL; i++) {
		if (http_methods[i].method_id == id) {
			name = http_methods[i].method_name;
			break;
		}
	}

	return (name);
}
