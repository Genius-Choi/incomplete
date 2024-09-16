static int ceph_x_encode_ticket(struct ceph_x_ticket_handler *th,
				void **p, void *end)
{
	ceph_decode_need(p, end, 1 + sizeof(u64), bad);
	ceph_encode_8(p, 1);
	ceph_encode_64(p, th->secret_id);
	if (th->ticket_blob) {
		const char *buf = th->ticket_blob->vec.iov_base;
		u32 len = th->ticket_blob->vec.iov_len;

		ceph_encode_32_safe(p, end, len, bad);
		ceph_encode_copy_safe(p, end, buf, len, bad);
	} else {
		ceph_encode_32_safe(p, end, 0, bad);
	}

	return 0;
bad:
	return -ERANGE;
}
