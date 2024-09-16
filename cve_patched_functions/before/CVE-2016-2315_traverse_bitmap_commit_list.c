void traverse_bitmap_commit_list(show_reachable_fn show_reachable)
{
	assert(bitmap_git.result);

	show_objects_for_type(bitmap_git.result, bitmap_git.commits,
		OBJ_COMMIT, show_reachable);
	show_objects_for_type(bitmap_git.result, bitmap_git.trees,
		OBJ_TREE, show_reachable);
	show_objects_for_type(bitmap_git.result, bitmap_git.blobs,
		OBJ_BLOB, show_reachable);
	show_objects_for_type(bitmap_git.result, bitmap_git.tags,
		OBJ_TAG, show_reachable);

	show_extended_objects(bitmap_git.result, show_reachable);

	bitmap_free(bitmap_git.result);
	bitmap_git.result = NULL;
}
