keepalived_realloc(void *buffer, size_t size, const char *file,
		   const char *function, int line)
{
	return keepalived_free_realloc_common(buffer, size, file, function, line, true);
}
