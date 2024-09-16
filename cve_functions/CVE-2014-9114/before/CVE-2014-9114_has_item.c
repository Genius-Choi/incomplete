static int has_item(char *ary[], const char *item)
{
	char **p;

	for (p = ary; *p != NULL; p++)
		if (!strcmp(item, *p))
			return 1;
	return 0;
}
