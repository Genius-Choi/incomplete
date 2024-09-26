static void mutex_lock_double(struct mutex *a, struct mutex *b)
{
	if (b < a)
		swap(a, b);

	mutex_lock(a);
	mutex_lock_nested(b, SINGLE_DEPTH_NESTING);
}
