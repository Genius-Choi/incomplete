bool file_exist (const char *filename)
{
	struct stat sbuffer;
	return (stat(filename, &sbuffer) == 0);
}
