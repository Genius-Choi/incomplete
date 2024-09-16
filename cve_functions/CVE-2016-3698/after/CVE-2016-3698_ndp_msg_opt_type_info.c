struct ndp_msg_opt_type_info *ndp_msg_opt_type_info(enum ndp_msg_opt_type msg_opt_type)
{
	return &ndp_msg_opt_type_info_list[msg_opt_type];
}
