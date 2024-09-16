char *get_component(char *target, char **targname)
{
	char *start;

	while(*target == '/')
		target ++;

	start = target;
	while(*target != '/' && *target != '\0')
		target ++;

	*targname = strndup(start, target - start);

	while(*target == '/')
		target ++;

	return target;
}
