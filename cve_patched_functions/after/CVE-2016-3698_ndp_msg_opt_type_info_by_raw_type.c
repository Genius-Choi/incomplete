struct ndp_msg_opt_type_info *ndp_msg_opt_type_info_by_raw_type(uint8_t raw_type)
{
	struct ndp_msg_opt_type_info *info;
	int i;

	for (i = 0; i < NDP_MSG_OPT_TYPE_LIST_SIZE; i++) {
		info = &ndp_msg_opt_type_info_list[i];
		if (info->raw_type == raw_type)
			return info;
	}
	return NULL;
}
