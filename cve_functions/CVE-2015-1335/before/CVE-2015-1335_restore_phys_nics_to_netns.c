void restore_phys_nics_to_netns(int netnsfd, struct lxc_conf *conf)
{
	int i, ret, oldfd;
	char path[MAXPATHLEN];

	if (netnsfd < 0)
		return;

	ret = snprintf(path, MAXPATHLEN, "/proc/self/ns/net");
	if (ret < 0 || ret >= MAXPATHLEN) {
		WARN("Failed to open monitor netns fd");
		return;
	}
	if ((oldfd = open(path, O_RDONLY)) < 0) {
		SYSERROR("Failed to open monitor netns fd");
		return;
	}
	if (setns(netnsfd, 0) != 0) {
		SYSERROR("Failed to enter container netns to reset nics");
		close(oldfd);
		return;
	}
	for (i=0; i<conf->num_savednics; i++) {
		struct saved_nic *s = &conf->saved_nics[i];
		if (lxc_netdev_move_by_index(s->ifindex, 1, NULL))
			WARN("Error moving nic index:%d back to host netns",
					s->ifindex);
	}
	if (setns(oldfd, 0) != 0)
		SYSERROR("Failed to re-enter monitor's netns");
	close(oldfd);
}
