fetch_name(OnigCodePoint start_code, UChar** src, UChar* end,
	   UChar** rname_end, ScanEnv* env, int* rback_num, int ref)
{
  int r, is_num, sign;
  OnigCodePoint end_code;
  OnigCodePoint c = 0;
  UChar *name_end;
  OnigEncoding enc = env->enc;
  UChar *pnum_head;
  UChar *p = *src;
  PFETCH_READY;

  *rback_num = 0;

  end_code = get_name_end_code_point(start_code);

  *rname_end = name_end = end;
  r = 0;
  pnum_head = *src;
  is_num = 0;
  sign = 1;

  if (PEND) {
    return ONIGERR_EMPTY_GROUP_NAME;
  }
  else {
    PFETCH(c);
    if (c == end_code)
      return ONIGERR_EMPTY_GROUP_NAME;

    if (ONIGENC_IS_CODE_DIGIT(enc, c)) {
      is_num = 1;
    }
    else if (c == '-') {
      is_num = 2;
      sign = -1;
      pnum_head = p;
    }
    else {
      r = ONIGERR_INVALID_CHAR_IN_GROUP_NAME;
    }
  }

  while (!PEND) {
    name_end = p;

    PFETCH(c);
    if (c == end_code || c == ')') break;
    if (! ONIGENC_IS_CODE_DIGIT(enc, c))
      r = ONIGERR_INVALID_CHAR_IN_GROUP_NAME;
  }
  if (r == 0 && c != end_code) {
    r = ONIGERR_INVALID_GROUP_NAME;
    name_end = end;
  }

  if (r == 0) {
    *rback_num = onig_scan_unsigned_number(&pnum_head, name_end, enc);
    if (*rback_num < 0) return ONIGERR_TOO_BIG_NUMBER;
    else if (*rback_num == 0) {
      r = ONIGERR_INVALID_GROUP_NAME;
      goto err;
    }
    *rback_num *= sign;

    *rname_end = name_end;
    *src = p;
    return 0;
  }
  else {
  err:
    onig_scan_env_set_error_string(env, r, *src, name_end);
    return r;
  }
}
