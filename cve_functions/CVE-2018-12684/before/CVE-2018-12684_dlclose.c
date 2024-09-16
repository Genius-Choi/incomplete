dlclose(void *handle)
{
	int result;

	if (FreeLibrary((HMODULE)handle) != 0) {
		result = 0;
	} else {
		result = -1;
	}

	return result;
}
