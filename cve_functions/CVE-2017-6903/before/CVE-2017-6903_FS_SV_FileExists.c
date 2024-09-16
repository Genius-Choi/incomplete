qboolean FS_SV_FileExists( const char *file )
{
	char *testpath;

	testpath = FS_BuildOSPath( fs_homepath->string, file, "");
	testpath[strlen(testpath)-1] = '\0';

	return FS_FileInPathExists(testpath);
}
