smb_ofile_release(smb_ofile_t *of)
{
	SMB_OFILE_VALID(of);

	mutex_enter(&of->f_mutex);
	ASSERT(of->f_refcnt);
	of->f_refcnt--;
	switch (of->f_state) {
	case SMB_OFILE_STATE_OPEN:
	case SMB_OFILE_STATE_CLOSING:
		break;

	case SMB_OFILE_STATE_CLOSED:
		if (of->f_refcnt == 0)
			smb_tree_post_ofile(of->f_tree, of);
		break;

	default:
		ASSERT(0);
		break;
	}
	mutex_exit(&of->f_mutex);
}
