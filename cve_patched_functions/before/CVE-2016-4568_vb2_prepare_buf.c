int vb2_prepare_buf(struct vb2_queue *q, struct v4l2_buffer *b)
{
	int ret;

	if (vb2_fileio_is_active(q)) {
		dprintk(1, "file io in progress\n");
		return -EBUSY;
	}

	ret = vb2_queue_or_prepare_buf(q, b, "prepare_buf");

	return ret ? ret : vb2_core_prepare_buf(q, b->index, b);
}
