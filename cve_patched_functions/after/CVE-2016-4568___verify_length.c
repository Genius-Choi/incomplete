static int __verify_length(struct vb2_buffer *vb, const struct v4l2_buffer *b)
{
	unsigned int length;
	unsigned int bytesused;
	unsigned int plane;

	if (!V4L2_TYPE_IS_OUTPUT(b->type))
		return 0;

	if (V4L2_TYPE_IS_MULTIPLANAR(b->type)) {
		for (plane = 0; plane < vb->num_planes; ++plane) {
			length = (b->memory == VB2_MEMORY_USERPTR ||
				  b->memory == VB2_MEMORY_DMABUF)
			       ? b->m.planes[plane].length
				: vb->planes[plane].length;
			bytesused = b->m.planes[plane].bytesused
				  ? b->m.planes[plane].bytesused : length;

			if (b->m.planes[plane].bytesused > length)
				return -EINVAL;

			if (b->m.planes[plane].data_offset > 0 &&
			    b->m.planes[plane].data_offset >= bytesused)
				return -EINVAL;
		}
	} else {
		length = (b->memory == VB2_MEMORY_USERPTR)
			? b->length : vb->planes[0].length;

		if (b->bytesused > length)
			return -EINVAL;
	}

	return 0;
}
