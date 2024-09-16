SMB2_lease_break(const unsigned int xid, struct cifs_tcon *tcon,
		 __u8 *lease_key, const __le32 lease_state)
{
	int rc;
	struct smb2_lease_ack *req = NULL;

	cifs_dbg(FYI, "SMB2_lease_break\n");
	rc = small_smb2_init(SMB2_OPLOCK_BREAK, tcon, (void **) &req);

	if (rc)
		return rc;

	req->hdr.CreditRequest = cpu_to_le16(1);
	req->StructureSize = cpu_to_le16(36);
	inc_rfc1001_len(req, 12);

	memcpy(req->LeaseKey, lease_key, 16);
	req->LeaseState = lease_state;

	rc = SendReceiveNoRsp(xid, tcon->ses, (char *) req, CIFS_OBREAK_OP);
	/* SMB2 buffer freed by function above */

	if (rc) {
		cifs_stats_fail_inc(tcon, SMB2_OPLOCK_BREAK_HE);
		cifs_dbg(FYI, "Send error in Lease Break = %d\n", rc);
	}

	return rc;
}
