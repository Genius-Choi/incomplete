static int uv__process_open_stream(uv_stdio_container_t* container,
                                   int pipefds[2],
                                   int writable) {
  int flags;

  if (!(container->flags & UV_CREATE_PIPE) || pipefds[0] < 0)
    return 0;

  if (uv__close(pipefds[1]))
    if (errno != EINTR && errno != EINPROGRESS)
      abort();

  pipefds[1] = -1;
  uv__nonblock(pipefds[0], 1);

  if (container->data.stream->type == UV_NAMED_PIPE &&
      ((uv_pipe_t*)container->data.stream)->ipc)
    flags = UV_STREAM_READABLE | UV_STREAM_WRITABLE;
  else if (writable)
    flags = UV_STREAM_WRITABLE;
  else
    flags = UV_STREAM_READABLE;

  return uv__stream_open(container->data.stream, pipefds[0], flags);
}
