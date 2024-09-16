void DirectoryListing(std::vector<std::string>& entries, const std::string &dir, bool bInclDirs, bool bInclFiles)
{
	DIR *d = NULL;
	struct dirent *ent;
	if ((d = opendir(dir.c_str())) != NULL)
	{
		while ((ent = readdir(d)) != NULL) {
			std::string name = ent->d_name;
			if (bInclDirs && dirent_is_directory(dir, ent) && name != "." && name != "..") {
				entries.push_back(name);
				continue;
			}
			if (bInclFiles && dirent_is_file(dir, ent)) {
				entries.push_back(name);
				continue;
			}
		}
		closedir(d);
	}
	return;
}
