set_uid_gid(const char *username, const char *groupname, uid_t *uid_p, gid_t *gid_p, bool default_user)
{
	uid_t uid;
	gid_t gid;
	struct passwd pwd;
	struct passwd *pwd_p;
	struct group grp;
	struct group *grp_p;
	int ret;
	bool using_default_default_user = false;

	if (!getpwnam_buf_len)
		set_pwnam_buf_len();

	{
		char buf[getpwnam_buf_len];

		if (default_user && !username) {
			using_default_default_user = true;
			username = "keepalived_script";
		}

		if ((ret = getpwnam_r(username, &pwd, buf, sizeof(buf), &pwd_p))) {
			log_message(LOG_INFO, "Unable to resolve %sscript username '%s' - ignoring", default_user ? "default " : "", username);
			return true;
		}
		if (!pwd_p) {
			if (using_default_default_user)
				log_message(LOG_INFO, "WARNING - default user '%s' for script execution does not exist - please create.", username);
			else
				log_message(LOG_INFO, "%script user '%s' does not exist", default_user ? "Default s" : "S", username);
			return true;
		}

		uid = pwd.pw_uid;
		gid = pwd.pw_gid;

		if (groupname) {
			if ((ret = getgrnam_r(groupname, &grp, buf, sizeof(buf), &grp_p))) {
				log_message(LOG_INFO, "Unable to resolve %sscript group name '%s' - ignoring", default_user ? "default " : "", groupname);
				return true;
			}
			if (!grp_p) {
				log_message(LOG_INFO, "%script group '%s' does not exist", default_user ? "Default s" : "S", groupname);
				return true;
			}
			gid = grp.gr_gid;
		}

		*uid_p = uid;
		*gid_p = gid;
	}

	return false;
}
