get_pfxmatch(
	char ** s,
	struct masks *m
	)
{
	while (m->name) {
		if (strncmp(*s, m->name, strlen(m->name)) == 0) {
			*s += strlen(m->name);
			return m->mask;
		} else {
			m++;
		}
	}
	return 0;
}
