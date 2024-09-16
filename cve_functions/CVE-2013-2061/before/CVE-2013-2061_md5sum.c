md5sum (uint8_t *buf, int len, int n_print_chars, struct gc_arena *gc)
{
  uint8_t digest[MD5_DIGEST_LENGTH];
  const md_kt_t *md5_kt = md_kt_get("MD5");

  md_full(md5_kt, buf, len, digest);

  return format_hex (digest, MD5_DIGEST_LENGTH, n_print_chars, gc);
}
