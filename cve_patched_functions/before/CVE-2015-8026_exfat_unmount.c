void exfat_unmount(struct exfat* ef)
{
	exfat_flush(ef);	/* ignore return code */
	exfat_put_node(ef, ef->root);
	exfat_reset_cache(ef);
	free(ef->root);
	ef->root = NULL;
	finalize_super_block(ef);
	exfat_close(ef->dev);	/* close descriptor immediately after fsync */
	ef->dev = NULL;
	free(ef->zero_cluster);
	ef->zero_cluster = NULL;
	free(ef->cmap.chunk);
	ef->cmap.chunk = NULL;
	free(ef->sb);
	ef->sb = NULL;
	free(ef->upcase);
	ef->upcase = NULL;
	ef->upcase_chars = 0;
}
