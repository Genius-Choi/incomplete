static int parse_number_sign(const char *input, char **endptr, int *sign)
{
	int sign_ = 1;

	while (i_isspace(*input))
		input++;

	if (*input == '-') {
		sign_ = -sign_;
		input++;
	}

	*sign = sign_;
	*endptr = (char *) input;
	return TRUE;
}
