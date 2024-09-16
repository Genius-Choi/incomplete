int is_numeric(const char *str, char end_char)
{
	g_return_val_if_fail(str != NULL, FALSE);

	if (*str == '\0' || *str == end_char)
		return FALSE;

	while (*str != '\0' && *str != end_char) {
		if (!i_isdigit(*str)) return FALSE;
		str++;
	}

	return TRUE;
}
