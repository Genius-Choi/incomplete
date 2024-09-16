static void file_change(struct diff_options *options,
		 unsigned old_mode, unsigned new_mode,
		 const unsigned char *old_sha1,
		 const unsigned char *new_sha1,
		 int old_sha1_valid, int new_sha1_valid,
		 const char *fullpath,
		 unsigned old_dirty_submodule, unsigned new_dirty_submodule)
{
	tree_difference = REV_TREE_DIFFERENT;
	DIFF_OPT_SET(options, HAS_CHANGES);
}
