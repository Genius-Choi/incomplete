static int vb2_internal_qbuf(struct vb2_queue *q, struct v4l2_buffer *b)
{
	int ret = vb2_queue_or_prepare_buf(q, b, "qbuf");

	return ret ? ret : vb2_core_qbuf(q, b->index, b);
}
