static int fsmChown(const char *path, mode_t mode, uid_t uid, gid_t gid)
{
    int rc = S_ISLNK(mode) ? lchown(path, uid, gid) : chown(path, uid, gid);
    if (rc < 0) {
	struct stat st;
	if (lstat(path, &st) == 0 && st.st_uid == uid && st.st_gid == gid)
	    rc = 0;
    }
    if (_fsm_debug)
	rpmlog(RPMLOG_DEBUG, " %8s (%s, %d, %d) %s\n", __func__,
	       path, (int)uid, (int)gid,
	       (rc < 0 ? strerror(errno) : ""));
    if (rc < 0)	rc = RPMERR_CHOWN_FAILED;
    return rc;
}
