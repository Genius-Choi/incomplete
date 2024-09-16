rend_service_parse_intro_for_v3(
    rend_intro_cell_t *intro,
    const uint8_t *buf,
    size_t plaintext_len,
    char **err_msg_out)
{
  ssize_t adjust, v2_ver_specific_len, ts_offset;

  /* This should only be called on v3 cells */
  if (intro->version != 3) {
    if (err_msg_out)
      tor_asprintf(err_msg_out,
                   "rend_service_parse_intro_for_v3() called with "
                   "bad version %d on INTRODUCE%d cell (this is a bug)",
                   intro->version,
                   (int)(intro->type));
    goto err;
  }

  /*
   * Check that we have at least enough to get auth_len:
   *
   * 1 octet for version, 1 for auth_type, 2 for auth_len
   */
  if (plaintext_len < 4) {
    if (err_msg_out) {
      tor_asprintf(err_msg_out,
                   "truncated plaintext of encrypted parted of "
                   "version %d INTRODUCE%d cell",
                   intro->version,
                   (int)(intro->type));
    }

    goto err;
  }

  /*
   * The rend_client_send_introduction() function over in rendclient.c is
   * broken (i.e., fails to match the spec) in such a way that we can't
   * change it without breaking the protocol.  Specifically, it doesn't
   * emit auth_len when auth-type is REND_NO_AUTH, so everything is off
   * by two bytes after that.  Calculate ts_offset and do everything from
   * the timestamp on relative to that to handle this dain bramage.
   */

  intro->u.v3.auth_type = buf[1];
  if (intro->u.v3.auth_type != REND_NO_AUTH) {
    intro->u.v3.auth_len = ntohs(get_uint16(buf + 2));
    ts_offset = 4 + intro->u.v3.auth_len;
  } else {
    intro->u.v3.auth_len = 0;
    ts_offset = 2;
  }

  /* Check that auth len makes sense for this auth type */
  if (intro->u.v3.auth_type == REND_BASIC_AUTH ||
      intro->u.v3.auth_type == REND_STEALTH_AUTH) {
      if (intro->u.v3.auth_len != REND_DESC_COOKIE_LEN) {
        if (err_msg_out) {
          tor_asprintf(err_msg_out,
                       "wrong auth data size %d for INTRODUCE%d cell, "
                       "should be %d",
                       (int)(intro->u.v3.auth_len),
                       (int)(intro->type),
                       REND_DESC_COOKIE_LEN);
        }

        goto err;
      }
  }

  /* Check that we actually have everything up through the timestamp */
  if (plaintext_len < (size_t)(ts_offset)+4) {
    if (err_msg_out) {
      tor_asprintf(err_msg_out,
                   "truncated plaintext of encrypted parted of "
                   "version %d INTRODUCE%d cell",
                   intro->version,
                   (int)(intro->type));
    }

    goto err;
  }

  if (intro->u.v3.auth_type != REND_NO_AUTH &&
      intro->u.v3.auth_len > 0) {
    /* Okay, we can go ahead and copy auth_data */
    intro->u.v3.auth_data = tor_malloc(intro->u.v3.auth_len);
    /*
     * We know we had an auth_len field in this case, so 4 is
     * always right.
     */
    memcpy(intro->u.v3.auth_data, buf + 4, intro->u.v3.auth_len);
  }

  /*
   * From here on, the format is as in v2, so we call the v2 parser with
   * adjusted buffer and length.  We are 4 + ts_offset octets in, but the
   * v2 parser expects to skip over a version byte at the start, so we
   * adjust by 3 + ts_offset.
   */
  adjust = 3 + ts_offset;

  v2_ver_specific_len =
    rend_service_parse_intro_for_v2(intro,
                                    buf + adjust, plaintext_len - adjust,
                                    err_msg_out);

  /* Success in v2 parser */
  if (v2_ver_specific_len >= 0) return v2_ver_specific_len + adjust;
  /* Failure in v2 parser; it will have provided an err_msg */
  else return v2_ver_specific_len;

 err:
  return -1;
}
