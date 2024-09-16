static char *build_dest_dir(const char *full_path) {
	assert(full_path);
	if (strstr(full_path, "/x86_64-linux-gnu/"))
		return RUN_LIB_DIR "/x86_64-linux-gnu";
	return RUN_LIB_DIR;
}
