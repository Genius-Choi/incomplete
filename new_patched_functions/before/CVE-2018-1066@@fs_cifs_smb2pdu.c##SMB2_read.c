SMB2_read(const unsigned int xid, struct cifs_io_parms *io_parms,
	  unsigned int *nbytes, char **buf, int *buf_type)
{
	int resp_buftype, rc = -EACCES;
	struct smb2_read_plain_req *req = NULL;
	struct smb2_read_rsp *rsp = NULL;
	struct smb2_sync_hdr *shdr;
	struct kvec iov[2];
	struct kvec rsp_iov;
	unsigned int total_len;
	__be32 req_len;
	struct smb_rqst rqst = { .rq_iov = iov,
				 .rq_nvec = 2 };
	int flags = CIFS_LOG_ERROR;
	struct cifs_ses *ses = io_parms->tcon->ses;

	*nbytes = 0;
	rc = smb2_new_read_req((void **)&req, &total_len, io_parms, 0, 0);
	if (rc)
		return rc;

	if (encryption_required(io_parms->tcon))
		flags |= CIFS_TRANSFORM_REQ;

	req_len = cpu_to_be32(total_len);

	iov[0].iov_base = &req_len;
	iov[0].iov_len = sizeof(__be32);
	iov[1].iov_base = req;
	iov[1].iov_len = total_len;

	rc = cifs_send_recv(xid, ses, &rqst, &resp_buftype, flags, &rsp_iov);
	cifs_small_buf_release(req);

	rsp = (struct smb2_read_rsp *)rsp_iov.iov_base;
	shdr = get_sync_hdr(rsp);

	if (shdr->Status == STATUS_END_OF_FILE) {
		free_rsp_buf(resp_buftype, rsp_iov.iov_base);
		return 0;
	}

	if (rc) {
		cifs_stats_fail_inc(io_parms->tcon, SMB2_READ_HE);
		cifs_dbg(VFS, "Send error in read = %d\n", rc);
	} else {
		*nbytes = le32_to_cpu(rsp->DataLength);
		if ((*nbytes > CIFS_MAX_MSGSIZE) ||
		    (*nbytes > io_parms->length)) {
			cifs_dbg(FYI, "bad length %d for count %d\n",
				 *nbytes, io_parms->length);
			rc = -EIO;
			*nbytes = 0;
		}
	}

	if (*buf) {
		memcpy(*buf, (char *)shdr + rsp->DataOffset, *nbytes);
		free_rsp_buf(resp_buftype, rsp_iov.iov_base);
	} else if (resp_buftype != CIFS_NO_BUFFER) {
		*buf = rsp_iov.iov_base;
		if (resp_buftype == CIFS_SMALL_BUFFER)
			*buf_type = CIFS_SMALL_BUFFER;
		else if (resp_buftype == CIFS_LARGE_BUFFER)
			*buf_type = CIFS_LARGE_BUFFER;
	}
	return rc;
}
