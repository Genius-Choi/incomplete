ssize_t add_to_pipe(struct pipe_inode_info *pipe, struct pipe_buffer *buf)
{
	int ret;

	if (unlikely(!pipe->readers)) {
		send_sig(SIGPIPE, current, 0);
		ret = -EPIPE;
	} else if (pipe->nrbufs == pipe->buffers) {
		ret = -EAGAIN;
	} else {
		int newbuf = (pipe->curbuf + pipe->nrbufs) & (pipe->buffers - 1);
		pipe->bufs[newbuf] = *buf;
		pipe->nrbufs++;
		return buf->len;
	}
	pipe_buf_release(pipe, buf);
	return ret;
}
