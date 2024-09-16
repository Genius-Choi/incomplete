rend_service_parse_intro_for_v2(
    rend_intro_cell_t *intro,
    const uint8_t *buf,
    size_t plaintext_len,
    char **err_msg_out)
{
  unsigned int klen;
  extend_info_t *extend_info = NULL;
  ssize_t ver_specific_len;

  /*
   * We accept version 3 too so that the v3 parser can call this with
   * an adjusted buffer for the latter part of a v3 cell, which is
   * identical to a v2 cell.
   */
  if (!(intro->version == 2 ||
        intro->version == 3)) {
    if (err_msg_out)
      tor_asprintf(err_msg_out,
                   "rend_service_parse_intro_for_v2() called with "
                   "bad version %d on INTRODUCE%d cell (this is a bug)",
                   intro->version,
                   (int)(intro->type));
    goto err;
  }

  /* 7 == version, IP and port, DIGEST_LEN == id, 2 == key length */
  if (plaintext_len < 7 + DIGEST_LEN + 2) {
    if (err_msg_out) {
      tor_asprintf(err_msg_out,
                   "truncated plaintext of encrypted parted of "
                   "version %d INTRODUCE%d cell",
                   intro->version,
                   (int)(intro->type));
    }

    goto err;
  }

  extend_info = tor_malloc_zero(sizeof(extend_info_t));
  tor_addr_from_ipv4n(&extend_info->addr, get_uint32(buf + 1));
  extend_info->port = ntohs(get_uint16(buf + 5));
  memcpy(extend_info->identity_digest, buf + 7, DIGEST_LEN);
  extend_info->nickname[0] = '$';
  base16_encode(extend_info->nickname + 1, sizeof(extend_info->nickname) - 1,
                extend_info->identity_digest, DIGEST_LEN);
  klen = ntohs(get_uint16(buf + 7 + DIGEST_LEN));

  /* 7 == version, IP and port, DIGEST_LEN == id, 2 == key length */
  if (plaintext_len < 7 + DIGEST_LEN + 2 + klen) {
    if (err_msg_out) {
      tor_asprintf(err_msg_out,
                   "truncated plaintext of encrypted parted of "
                   "version %d INTRODUCE%d cell",
                   intro->version,
                   (int)(intro->type));
    }

    goto err;
  }

  extend_info->onion_key =
    crypto_pk_asn1_decode((const char *)(buf + 7 + DIGEST_LEN + 2), klen);
  if (!extend_info->onion_key) {
    if (err_msg_out) {
      tor_asprintf(err_msg_out,
                   "error decoding onion key in version %d "
                   "INTRODUCE%d cell",
                   intro->version,
                   (intro->type));
    }

    goto err;
  }
  if (128 != crypto_pk_keysize(extend_info->onion_key)) {
    if (err_msg_out) {
      tor_asprintf(err_msg_out,
                   "invalid onion key size in version %d INTRODUCE%d cell",
                   intro->version,
                   (intro->type));
    }

    goto err;
  }

  ver_specific_len = 7+DIGEST_LEN+2+klen;

  if (intro->version == 2) intro->u.v2.extend_info = extend_info;
  else intro->u.v3.extend_info = extend_info;

  return ver_specific_len;

 err:
  extend_info_free(extend_info);

  return -1;
}
