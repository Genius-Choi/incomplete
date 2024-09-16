time2timeval(mrb_state *mrb, mrb_value time)
{
  struct timeval t = { 0, 0 };

  switch (mrb_type(time)) {
    case MRB_TT_FIXNUM:
      t.tv_sec = (ftime_t)mrb_fixnum(time);
      t.tv_usec = 0;
      break;

#ifndef MRB_WITHOUT_FLOAT
    case MRB_TT_FLOAT:
      t.tv_sec = (ftime_t)mrb_float(time);
      t.tv_usec = (fsuseconds_t)((mrb_float(time) - t.tv_sec) * 1000000.0);
      break;
#endif

    default:
      mrb_raise(mrb, E_TYPE_ERROR, "wrong argument class");
  }

  return t;
}
