is_executable(struct stat *buf, uid_t uid, gid_t gid)
{
	return (uid == 0 && buf->st_mode & (S_IXUSR | S_IXGRP | S_IXOTH)) ||
	       (uid == buf->st_uid && buf->st_mode & S_IXUSR) ||
	       (uid != buf->st_uid &&
		((gid == buf->st_gid && buf->st_mode & S_IXGRP) ||
		 (gid != buf->st_gid && buf->st_mode & S_IXOTH)));
}
