mrb_io_sysread(mrb_state *mrb, mrb_value io)
{
  struct mrb_io *fptr;
  mrb_value buf = mrb_nil_value();
  mrb_int maxlen;
  int ret;

  mrb_get_args(mrb, "i|S", &maxlen, &buf);
  if (maxlen < 0) {
    mrb_raise(mrb, E_ARGUMENT_ERROR, "negative expanding string size");
  }
  else if (maxlen == 0) {
    return mrb_str_new(mrb, NULL, maxlen);
  }

  if (mrb_nil_p(buf)) {
    buf = mrb_str_new(mrb, NULL, maxlen);
  }

  if (RSTRING_LEN(buf) != maxlen) {
    buf = mrb_str_resize(mrb, buf, maxlen);
  } else {
    mrb_str_modify(mrb, RSTRING(buf));
  }

  fptr = (struct mrb_io *)io_get_open_fptr(mrb, io);
  if (!fptr->readable) {
    mrb_raise(mrb, E_IO_ERROR, "not opened for reading");
  }
  ret = read(fptr->fd, RSTRING_PTR(buf), (fsize_t)maxlen);
  switch (ret) {
    case 0: /* EOF */
      if (maxlen == 0) {
        buf = mrb_str_new_cstr(mrb, "");
      } else {
        mrb_raise(mrb, E_EOF_ERROR, "sysread failed: End of File");
      }
      break;
    case -1: /* Error */
      mrb_sys_fail(mrb, "sysread failed");
      break;
    default:
      if (RSTRING_LEN(buf) != ret) {
        buf = mrb_str_resize(mrb, buf, ret);
      }
      break;
  }

  return buf;
}
