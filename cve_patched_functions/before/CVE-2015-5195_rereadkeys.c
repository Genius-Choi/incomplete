rereadkeys(void)
{
	if (NULL != key_file_name)
		authreadkeys(key_file_name);
}
