void FixFolderEnding(std::string &folder)
{
#if defined(WIN32)
	if (folder.at(folder.length() - 1) != '\\')
		folder += "\\";
#else
	if (folder.at(folder.length() - 1) != '/')
		folder += "/";
#endif
}
