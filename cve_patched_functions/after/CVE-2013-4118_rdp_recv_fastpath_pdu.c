static int rdp_recv_fastpath_pdu(rdpRdp* rdp, STREAM* s)
{
	UINT16 length;
	rdpFastPath* fastpath;

	fastpath = rdp->fastpath;

	if (!fastpath_read_header_rdp(fastpath, s, &length))
		return -1;

	if ((length == 0) || (length > stream_get_left(s)))
	{
		printf("incorrect FastPath PDU header length %d\n", length);
		return -1;
	}

	if (fastpath->encryptionFlags & FASTPATH_OUTPUT_ENCRYPTED)
	{
		UINT16 flags = (fastpath->encryptionFlags & FASTPATH_OUTPUT_SECURE_CHECKSUM) ? SEC_SECURE_CHECKSUM : 0;

		if (!rdp_decrypt(rdp, s, length, flags))
			return -1;
	}

	return fastpath_recv_updates(rdp->fastpath, s);
}
