static inline void inc_rfc1001_len(void *pSMB, int count)
{
	struct smb_hdr *hdr = (struct smb_hdr *)pSMB;

	be32_add_cpu(&hdr->smb_buf_length, count);
}
