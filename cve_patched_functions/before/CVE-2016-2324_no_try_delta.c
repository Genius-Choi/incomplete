static int no_try_delta(const char *path)
{
	struct git_attr_check check[1];

	setup_delta_attr_check(check);
	if (git_check_attr(path, ARRAY_SIZE(check), check))
		return 0;
	if (ATTR_FALSE(check->value))
		return 1;
	return 0;
}
