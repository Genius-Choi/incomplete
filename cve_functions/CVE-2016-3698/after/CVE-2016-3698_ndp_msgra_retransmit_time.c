uint32_t ndp_msgra_retransmit_time(struct ndp_msgra *msgra)
{
	return ntohl(msgra->ra->nd_ra_retransmit);
}
