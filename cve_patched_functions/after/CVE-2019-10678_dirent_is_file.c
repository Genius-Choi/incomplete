bool dirent_is_file(const std::string &dir, struct dirent *ent)
{
	if (ent->d_type == DT_REG)
		return true;
#ifndef WIN32
	if (ent->d_type == DT_UNKNOWN) {
		std::string fname = dir + "/" + ent->d_name;
		struct stat st;
		if (!lstat(fname.c_str(), &st))
			return S_ISREG(st.st_mode);
	}
#endif
	return false;
}
