gss_release_iov_buffer (minor_status,
			iov,
			iov_count)
OM_uint32 *		minor_status;
gss_iov_buffer_desc *	iov;
int			iov_count;
{
    OM_uint32		status = GSS_S_COMPLETE;
    int			i;

    if (minor_status)
	*minor_status = 0;

    if (iov == GSS_C_NO_IOV_BUFFER)
	return GSS_S_COMPLETE;

    for (i = 0; i < iov_count; i++) {
	if (iov[i].type & GSS_IOV_BUFFER_FLAG_ALLOCATED) {
	    status = gss_release_buffer(minor_status, &iov[i].buffer);
	    if (status != GSS_S_COMPLETE)
		break;

	    iov[i].type &= ~(GSS_IOV_BUFFER_FLAG_ALLOCATED);
	}
    }

    return status;
}
