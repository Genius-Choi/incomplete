bool dirent_is_directory(const std::string &dir, struct dirent *ent)
{
	if (ent->d_type == DT_DIR)
		return true;
#ifndef WIN32
	if (ent->d_type == DT_LNK)
		return true;
	if (ent->d_type == DT_UNKNOWN) {
		std::string fname = dir + "/" + ent->d_name;
		struct stat st;
		if (!lstat(fname.c_str(), &st))
			return S_ISDIR(st.st_mode);
	}
#endif
	return false;
}
