long_help(void)
{
	const char	*prog;
	const char	*p;

	prog = lafe_getprogname();

	fflush(stderr);

	p = (strcmp(prog,"bsdcpio") != 0) ? "(bsdcpio)" : "";
	printf("%s%s: manipulate archive files\n", prog, p);

	for (p = long_help_msg; *p != '\0'; p++) {
		if (*p == '%') {
			if (p[1] == 'p') {
				fputs(prog, stdout);
				p++;
			} else
				putchar('%');
		} else
			putchar(*p);
	}
	version();
}
