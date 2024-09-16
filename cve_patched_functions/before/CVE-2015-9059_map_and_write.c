map_and_write (int fd, int map, char c)
{
	char b[M_MAXMAP];
	int n;
		
	n = do_map(b, map, c);
	if ( n )
		if ( writen_ni(fd, b, n) < n )
			fatal("write to stdout failed: %s", strerror(errno));		
}
