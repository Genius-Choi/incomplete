static void nfsd4_open_deleg_none_ext(struct nfsd4_open *open, int status)
{
	open->op_delegate_type = NFS4_OPEN_DELEGATE_NONE_EXT;
	if (status == -EAGAIN)
		open->op_why_no_deleg = WND4_CONTENTION;
	else {
		open->op_why_no_deleg = WND4_RESOURCE;
		switch (open->op_deleg_want) {
		case NFS4_SHARE_WANT_READ_DELEG:
		case NFS4_SHARE_WANT_WRITE_DELEG:
		case NFS4_SHARE_WANT_ANY_DELEG:
			break;
		case NFS4_SHARE_WANT_CANCEL:
			open->op_why_no_deleg = WND4_CANCELLED;
			break;
		case NFS4_SHARE_WANT_NO_DELEG:
			WARN_ON_ONCE(1);
		}
	}
}
