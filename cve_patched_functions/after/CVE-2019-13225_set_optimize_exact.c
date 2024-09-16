set_optimize_exact(regex_t* reg, OptStr* e)
{
  int r;

  if (e->len == 0) return 0;

  reg->exact = (UChar* )xmalloc(e->len);
  CHECK_NULL_RETURN_MEMERR(reg->exact);
  xmemcpy(reg->exact, e->s, e->len);
  reg->exact_end = reg->exact + e->len;

  if (e->case_fold) {
    reg->optimize = OPTIMIZE_STR_CASE_FOLD;
    if (e->good_case_fold != 0) {
      if (e->len >= 2) {
        r = set_sunday_quick_search_or_bmh_skip_table(reg, 1,
                             reg->exact, reg->exact_end,
                             reg->map, &(reg->map_offset));
        if (r != 0) return r;
        reg->optimize = OPTIMIZE_STR_CASE_FOLD_FAST;
      }
    }
  }
  else {
    int allow_reverse;

    allow_reverse =
      ONIGENC_IS_ALLOWED_REVERSE_MATCH(reg->enc, reg->exact, reg->exact_end);

    if (e->len >= 2 || (e->len >= 1 && allow_reverse)) {
      r = set_sunday_quick_search_or_bmh_skip_table(reg, 0,
                                         reg->exact, reg->exact_end,
                                         reg->map, &(reg->map_offset));
      if (r != 0) return r;

      reg->optimize = (allow_reverse != 0
                       ? OPTIMIZE_STR_FAST
                       : OPTIMIZE_STR_FAST_STEP_FORWARD);
    }
    else {
      reg->optimize = OPTIMIZE_STR;
    }
  }

  reg->dmin = e->mmd.min;
  reg->dmax = e->mmd.max;

  if (reg->dmin != INFINITE_LEN) {
    reg->threshold_len = reg->dmin + (int )(reg->exact_end - reg->exact);
  }

  return 0;
}
