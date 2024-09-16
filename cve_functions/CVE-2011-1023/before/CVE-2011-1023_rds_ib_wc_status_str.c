char *rds_ib_wc_status_str(enum ib_wc_status status)
{
	return rds_str_array(rds_ib_wc_status_strings,
			     ARRAY_SIZE(rds_ib_wc_status_strings), status);
}
