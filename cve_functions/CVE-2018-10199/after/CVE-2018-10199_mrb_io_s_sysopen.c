mrb_io_s_sysopen(mrb_state *mrb, mrb_value klass)
{
  mrb_value path = mrb_nil_value();
  mrb_value mode = mrb_nil_value();
  mrb_int fd, perm = -1;
  const char *pat;
  int flags, modenum;

  mrb_get_args(mrb, "S|Si", &path, &mode, &perm);
  if (mrb_nil_p(mode)) {
    mode = mrb_str_new_cstr(mrb, "r");
  }
  if (perm < 0) {
    perm = 0666;
  }

  pat = mrb_string_value_cstr(mrb, &path);
  flags = mrb_io_modestr_to_flags(mrb, mrb_string_value_cstr(mrb, &mode));
  modenum = mrb_io_flags_to_modenum(mrb, flags);
  fd = mrb_cloexec_open(mrb, pat, modenum, perm);
  return mrb_fixnum_value(fd);
}
