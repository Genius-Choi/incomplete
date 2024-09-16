static void prune_init_slice(char *cg)
{
	char *point;
	point = cg + strlen(cg) - strlen(INITSCOPE);
	if (point < cg)
		 return;
	if (strcmp(point, INITSCOPE) == 0) {
		if (point == cg)
			*(point+1) = '\0';
		else
			*point = '\0';
	}
}
