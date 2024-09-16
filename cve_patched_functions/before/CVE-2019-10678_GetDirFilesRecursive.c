int GetDirFilesRecursive(const std::string &DirPath, std::map<std::string, int> &_Files)
{
	DIR* dir;
	if ((dir = opendir(DirPath.c_str())) != NULL)
	{
		struct dirent *ent;
		while ((ent = readdir(dir)) != NULL)
		{
			if (dirent_is_directory(DirPath, ent))
			{
				if ((strcmp(ent->d_name, ".") != 0) && (strcmp(ent->d_name, "..") != 0) && (strcmp(ent->d_name, ".svn") != 0))
				{
					std::string nextdir = DirPath + ent->d_name + "/";
					if (GetDirFilesRecursive(nextdir.c_str(), _Files))
					{
						closedir(dir);
						return 1;
					}
				}
			}
			else
			{
				std::string fname = DirPath + ent->d_name;
				_Files[fname] = 1;
			}
		}
	}
	closedir(dir);
	return 0;
}
