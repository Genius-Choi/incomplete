uoff_t str_to_uofft(const char *str)
{
#ifdef UOFF_T_LONG_LONG
	return (uoff_t)strtoull(str, NULL, 10);
#else
	return (uoff_t)strtoul(str, NULL, 10);
#endif
}
