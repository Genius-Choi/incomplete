int vb2_create_bufs(struct vb2_queue *q, struct v4l2_create_buffers *create)
{
	unsigned requested_planes = 1;
	unsigned requested_sizes[VIDEO_MAX_PLANES];
	struct v4l2_format *f = &create->format;
	int ret = vb2_verify_memory_type(q, create->memory, f->type);
	unsigned i;

	create->index = q->num_buffers;
	if (create->count == 0)
		return ret != -EBUSY ? ret : 0;

	switch (f->type) {
	case V4L2_BUF_TYPE_VIDEO_CAPTURE_MPLANE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT_MPLANE:
		requested_planes = f->fmt.pix_mp.num_planes;
		if (requested_planes == 0 ||
		    requested_planes > VIDEO_MAX_PLANES)
			return -EINVAL;
		for (i = 0; i < requested_planes; i++)
			requested_sizes[i] =
				f->fmt.pix_mp.plane_fmt[i].sizeimage;
		break;
	case V4L2_BUF_TYPE_VIDEO_CAPTURE:
	case V4L2_BUF_TYPE_VIDEO_OUTPUT:
		requested_sizes[0] = f->fmt.pix.sizeimage;
		break;
	case V4L2_BUF_TYPE_VBI_CAPTURE:
	case V4L2_BUF_TYPE_VBI_OUTPUT:
		requested_sizes[0] = f->fmt.vbi.samples_per_line *
			(f->fmt.vbi.count[0] + f->fmt.vbi.count[1]);
		break;
	case V4L2_BUF_TYPE_SLICED_VBI_CAPTURE:
	case V4L2_BUF_TYPE_SLICED_VBI_OUTPUT:
		requested_sizes[0] = f->fmt.sliced.io_size;
		break;
	case V4L2_BUF_TYPE_SDR_CAPTURE:
	case V4L2_BUF_TYPE_SDR_OUTPUT:
		requested_sizes[0] = f->fmt.sdr.buffersize;
		break;
	default:
		return -EINVAL;
	}
	for (i = 0; i < requested_planes; i++)
		if (requested_sizes[i] == 0)
			return -EINVAL;
	return ret ? ret : vb2_core_create_bufs(q, create->memory,
		&create->count, requested_planes, requested_sizes);
}
