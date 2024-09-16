bool_t auth_gssapi_unseal_seq(
     gss_ctx_id_t context,
     gss_buffer_t in_buf,
     uint32_t *seq_num)
{
     gss_buffer_desc out_buf;
     OM_uint32 gssstat, minor_stat;
     uint32_t nl_seq_num;

     gssstat = gss_unseal(&minor_stat, context, in_buf, &out_buf,
			  NULL, NULL);
     if (gssstat != GSS_S_COMPLETE) {
	  PRINTF(("gssapi_unseal_seq: failed\n"));
	  AUTH_GSSAPI_DISPLAY_STATUS(("unsealing sequence number",
				      gssstat, minor_stat));
	  return FALSE;
     } else if (out_buf.length != sizeof(uint32_t)) {
	  PRINTF(("gssapi_unseal_seq: unseal gave %d bytes\n",
		  (int) out_buf.length));
	  gss_release_buffer(&minor_stat, &out_buf);
	  return FALSE;
     }

     nl_seq_num = *((uint32_t *) out_buf.value);
     *seq_num = (uint32_t) ntohl(nl_seq_num);
     gss_release_buffer(&minor_stat, &out_buf);

     return TRUE;
}
