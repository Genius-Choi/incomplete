static void nlmsvc_release_block(struct nlm_block *block)
{
	if (block != NULL)
		kref_put_mutex(&block->b_count, nlmsvc_free_block, &block->b_file->f_mutex);
}
