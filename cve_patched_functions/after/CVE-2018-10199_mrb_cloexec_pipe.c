mrb_cloexec_pipe(mrb_state *mrb, int fildes[2])
{
  int ret;
  ret = pipe(fildes);
  if (ret == -1)
    return -1;
  mrb_fd_cloexec(mrb, fildes[0]);
  mrb_fd_cloexec(mrb, fildes[1]);
  return ret;
}
