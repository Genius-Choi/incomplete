static void ndp_msg_type_set(struct ndp_msg *msg, enum ndp_msg_type msg_type)
{
	msg->icmp6_hdr->icmp6_type = ndp_msg_type_info(msg_type)->raw_type;
}
