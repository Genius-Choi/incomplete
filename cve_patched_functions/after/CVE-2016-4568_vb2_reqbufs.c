int vb2_reqbufs(struct vb2_queue *q, struct v4l2_requestbuffers *req)
{
	int ret = vb2_verify_memory_type(q, req->memory, req->type);

	return ret ? ret : vb2_core_reqbufs(q, req->memory, &req->count);
}
