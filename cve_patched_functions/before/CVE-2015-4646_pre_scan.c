void pre_scan(char *parent_name, unsigned int start_block, unsigned int offset,
	struct pathnames *paths)
{
	unsigned int type;
	char *name;
	struct pathnames *new;
	struct inode *i;
	struct dir *dir = s_ops.squashfs_opendir(start_block, offset, &i);

	if(dir == NULL)
		return;

	while(squashfs_readdir(dir, &name, &start_block, &offset, &type)) {
		struct inode *i;
		char *pathname;
		int res;

		TRACE("pre_scan: name %s, start_block %d, offset %d, type %d\n",
			name, start_block, offset, type);

		if(!matches(paths, name, &new))
			continue;

		res = asprintf(&pathname, "%s/%s", parent_name, name);
		if(res == -1)
			EXIT_UNSQUASH("asprintf failed in dir_scan\n");

		if(type == SQUASHFS_DIR_TYPE)
			pre_scan(parent_name, start_block, offset, new);
		else if(new == NULL) {
			if(type == SQUASHFS_FILE_TYPE ||
					type == SQUASHFS_LREG_TYPE) {
				i = s_ops.read_inode(start_block, offset);
				if(created_inode[i->inode_number - 1] == NULL) {
					created_inode[i->inode_number - 1] =
						(char *) i;
					total_blocks += (i->data +
						(block_size - 1)) >> block_log;
				}
				total_files ++;
			}
			total_inodes ++;
		}

		free_subdir(new);
		free(pathname);
	}

	squashfs_closedir(dir);
}
