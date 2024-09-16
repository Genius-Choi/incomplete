notify_resource_release(void)
{
	if (path_is_malloced) {
		FREE(path);
		path_is_malloced = false;
		path = NULL;
	}
}
