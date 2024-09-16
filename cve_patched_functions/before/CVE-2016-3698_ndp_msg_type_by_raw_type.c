static int ndp_msg_type_by_raw_type(enum ndp_msg_type *p_msg_type,
				    uint8_t raw_type)
{
	int i;

	for (i = 0; i < NDP_MSG_TYPE_LIST_SIZE; i++) {
		if (ndp_msg_type_info(i)->raw_type == raw_type) {
			*p_msg_type = i;
			return 0;
		}
	}
	return -ENOENT;
}
