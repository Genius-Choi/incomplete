keepalived_free(void *buffer, const char *file, const char *function, int line)
{
	keepalived_free_realloc_common(buffer, 0, file, function, line, false);
}
