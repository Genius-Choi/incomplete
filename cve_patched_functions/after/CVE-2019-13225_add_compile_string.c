add_compile_string(UChar* s, int mb_len, int str_len,
                   regex_t* reg, int ignore_case)
{
  int op;
  int r;
  int byte_len;
  UChar* p;
  UChar* end;

  op = select_str_opcode(mb_len, str_len, ignore_case);
  r = add_op(reg, op);
  if (r != 0) return r;

  byte_len = mb_len * str_len;
  end = s + byte_len;

  if (op == OP_EXACTMBN) {
    p = onigenc_strdup(reg->enc, s, end);
    CHECK_NULL_RETURN_MEMERR(p);

    COP(reg)->exact_len_n.len = mb_len;
    COP(reg)->exact_len_n.n   = str_len;
    COP(reg)->exact_len_n.s   = p;
  }
  else if (IS_NEED_STR_LEN_OP_EXACT(op)) {
    p = onigenc_strdup(reg->enc, s, end);
    CHECK_NULL_RETURN_MEMERR(p);

    if (op == OP_EXACTN_IC)
      COP(reg)->exact_n.n = byte_len;
    else
      COP(reg)->exact_n.n = str_len;

    COP(reg)->exact_n.s = p;
  }
  else {
    xmemcpy(COP(reg)->exact.s, s, (size_t )byte_len);
    COP(reg)->exact.s[byte_len] = '\0';
  }

  return 0;
}
