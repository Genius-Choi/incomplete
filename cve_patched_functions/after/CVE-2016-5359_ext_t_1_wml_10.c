ext_t_1_wml_10(tvbuff_t *tvb, guint32 value, guint32 str_tbl)
{
	char *str = wmem_strdup_printf(wmem_packet_scope(), "Variable substitution - unescaped: '%s'",
				    tvb_get_const_stringz(tvb, str_tbl + value, NULL));
	return str;
}
