int set_attributes(char *pathname, int mode, uid_t uid, gid_t guid, time_t time,
	unsigned int xattr, unsigned int set_mode)
{
	struct utimbuf times = { time, time };

	if(utime(pathname, &times) == -1) {
		ERROR("set_attributes: failed to set time on %s, because %s\n",
			pathname, strerror(errno));
		return FALSE;
	}

	if(root_process) {
		if(chown(pathname, uid, guid) == -1) {
			ERROR("set_attributes: failed to change uid and gids "
				"on %s, because %s\n", pathname,
				strerror(errno));
			return FALSE;
		}
	} else
		mode &= ~07000;

	if((set_mode || (mode & 07000)) && chmod(pathname, (mode_t) mode) == -1) {
		ERROR("set_attributes: failed to change mode %s, because %s\n",
			pathname, strerror(errno));
		return FALSE;
	}

	write_xattr(pathname, xattr);

	return TRUE;
}
