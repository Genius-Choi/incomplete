mrb_mod_const_get(mrb_state *mrb, mrb_value mod)
{
  mrb_value path;
  mrb_sym id;
  char *ptr;
  mrb_int off, end, len;

  mrb_get_args(mrb, "o", &path);

  if (mrb_symbol_p(path)) {
    /* const get with symbol */
    id = mrb_symbol(path);
    return mrb_const_get_sym(mrb, mod, id);
  }

  /* const get with class path string */
  path = mrb_string_type(mrb, path);
  ptr = RSTRING_PTR(path);
  len = RSTRING_LEN(path);
  off = 0;

  while (off < len) {
    end = mrb_str_index_lit(mrb, path, "::", off);
    end = (end == -1) ? len : end;
    id = mrb_intern(mrb, ptr+off, end-off);
    mod = mrb_const_get_sym(mrb, mod, id);
    off = (end == len) ? end : end+2;
  }

  return mod;
}
