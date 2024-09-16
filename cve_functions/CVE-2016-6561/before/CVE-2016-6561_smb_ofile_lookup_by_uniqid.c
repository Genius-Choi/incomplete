smb_ofile_lookup_by_uniqid(smb_tree_t *tree, uint32_t uniqid)
{
	smb_llist_t	*of_list;
	smb_ofile_t	*of;

	ASSERT(tree->t_magic == SMB_TREE_MAGIC);

	of_list = &tree->t_ofile_list;
	smb_llist_enter(of_list, RW_READER);
	of = smb_llist_head(of_list);

	while (of) {
		ASSERT(of->f_magic == SMB_OFILE_MAGIC);
		ASSERT(of->f_tree == tree);

		if (of->f_uniqid == uniqid) {
			if (smb_ofile_hold(of)) {
				smb_llist_exit(of_list);
				return (of);
			}
		}

		of = smb_llist_next(of_list, of);
	}

	smb_llist_exit(of_list);
	return (NULL);
}
