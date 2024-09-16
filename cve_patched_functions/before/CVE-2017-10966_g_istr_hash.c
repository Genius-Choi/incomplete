guint g_istr_hash(gconstpointer v)
{
	const signed char *p;
	guint32 h = 5381;

	for (p = v; *p != '\0'; p++)
		h = (h << 5) + h + g_ascii_toupper(*p);

	return h;
}
