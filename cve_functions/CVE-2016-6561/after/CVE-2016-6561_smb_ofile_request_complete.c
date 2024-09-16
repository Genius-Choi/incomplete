smb_ofile_request_complete(smb_ofile_t *of)
{
	SMB_OFILE_VALID(of);

	switch (of->f_ftype) {
	case SMB_FTYPE_DISK:
		ASSERT(of->f_node);
		smb_oplock_broadcast(of->f_node);
		break;
	case SMB_FTYPE_MESG_PIPE:
		break;
	default:
		break;
	}
}
