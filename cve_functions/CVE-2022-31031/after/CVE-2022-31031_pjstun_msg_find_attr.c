PJ_DEF(void*) pjstun_msg_find_attr( pjstun_msg *msg, pjstun_attr_type t)
{
    int i;

    PJ_CHECK_STACK();

    for (i=0; i<msg->attr_count; ++i) {
	pjstun_attr_hdr *attr = msg->attr[i];
	if (pj_ntohs(attr->type) == t)
	    return attr;
    }

    return 0;
}
