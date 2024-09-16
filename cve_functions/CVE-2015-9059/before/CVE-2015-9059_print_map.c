print_map (int flags)
{
	int i;

	for (i = 0; i < M_NFLAGS; i++)
		if ( flags & (1 << i) )
			printf("%s,", map_names[i].name);
	printf("\n");
}
