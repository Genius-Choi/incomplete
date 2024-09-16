int vb2_qbuf(struct vb2_queue *q, struct v4l2_buffer *b)
{
	if (vb2_fileio_is_active(q)) {
		dprintk(1, "file io in progress\n");
		return -EBUSY;
	}

	return vb2_internal_qbuf(q, b);
}
