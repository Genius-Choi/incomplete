set_valid_path(char *valid_path, const char *path)
{
	const char *str_in;
	char *str_out;

	for (str_in = path, str_out = valid_path; *str_in; str_in++, str_out++) {
		if (!isalnum(*str_in))
			*str_out = '_';
		else
			*str_out = *str_in;
	}
	*str_out = '\0';

	return valid_path;
}
