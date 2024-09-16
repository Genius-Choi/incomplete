static int ceph_x_encrypt_buflen(int ilen)
{
	return sizeof(struct ceph_x_encrypt_header) + ilen + 16 +
		sizeof(u32);
}
