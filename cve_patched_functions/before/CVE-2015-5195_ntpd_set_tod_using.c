ntpd_set_tod_using(
	const char *which
	)
{
	char line[128];

	snprintf(line, sizeof(line), "settimeofday=\"%s\"", which);
	set_sys_var(line, strlen(line) + 1, RO);
}
