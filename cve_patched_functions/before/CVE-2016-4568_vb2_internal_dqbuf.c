static int vb2_internal_dqbuf(struct vb2_queue *q, struct v4l2_buffer *b,
		bool nonblocking)
{
	int ret;

	if (b->type != q->type) {
		dprintk(1, "invalid buffer type\n");
		return -EINVAL;
	}

	ret = vb2_core_dqbuf(q, NULL, b, nonblocking);

	return ret;
}
