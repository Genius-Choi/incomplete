alloc_email(char *addr)
{
	size_t size = strlen(addr);
	char *new;

	new = (char *) MALLOC(size + 1);
	memcpy(new, addr, size + 1);

	list_add(global_data->email, new);
}
