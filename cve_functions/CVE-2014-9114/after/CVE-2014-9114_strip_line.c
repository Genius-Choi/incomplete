static char *strip_line(char *line)
{
	char	*p;

	line = skip_over_blank(line);

	p = line + strlen(line) - 1;

	while (*line) {
		if (isspace(*p))
			*p-- = '\0';
		else
			break;
	}

	return line;
}
