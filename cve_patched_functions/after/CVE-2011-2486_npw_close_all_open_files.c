void npw_close_all_open_files(void)
{
  const int min_fd = 3;

#if defined(__linux__)
  DIR *dir = opendir("/proc/self/fd");
  if (dir) {
	const int dfd = dirfd(dir);
	struct dirent *d;
	while ((d = readdir(dir)) != NULL) {
	  char *end;
	  long n = strtol(d->d_name, &end, 10);
	  if (*end == '\0') {
		int fd = n;
		if (fd >= min_fd && fd != dfd)
		  close(fd);
	  }
	}
	closedir(dir);
	return;
  }
#endif

  const int open_max = get_open_max();
  for (int fd = min_fd; fd < open_max; fd++)
	close(fd);
}
