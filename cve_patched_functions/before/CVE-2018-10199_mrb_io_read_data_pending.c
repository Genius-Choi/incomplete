mrb_io_read_data_pending(mrb_state *mrb, mrb_value io)
{
  mrb_value buf = mrb_iv_get(mrb, io, mrb_intern_cstr(mrb, "@buf"));
  if (mrb_type(buf) == MRB_TT_STRING && RSTRING_LEN(buf) > 0) {
    return 1;
  }
  return 0;
}
