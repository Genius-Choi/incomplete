ext_t_0_wv_cspc_13(tvbuff_t *tvb _U_, guint32 value, guint32 str_tbl _U_)
{
	char *str = wmem_strdup_printf(wmem_packet_scope(), "Common Value: '%s'",
				    val_to_str(value, vals_wv_csp_13_element_value_tokens,
					       "<Unknown WV-CSP 1.3 Common Value token 0x%X>"));
	return str;
}
