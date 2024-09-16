static bool is_native_overlayfs(const char *path)
{
	struct statfs sb;

	if (statfs(path, &sb) < 0)
		return false;
	if (sb.f_type == OVERLAYFS_SUPER_MAGIC ||
			sb.f_type == OVERLAY_SUPER_MAGIC)
		return true;
	return false;
}
