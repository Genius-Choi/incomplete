static int pmcraid_notify_aen(
	struct pmcraid_instance *pinstance,
	struct pmcraid_aen_msg  *aen_msg,
	u32    data_size
)
{
	struct sk_buff *skb;
	void *msg_header;
	u32  total_size, nla_genl_hdr_total_size;
	int result;

	aen_msg->hostno = (pinstance->host->unique_id << 16 |
			   MINOR(pinstance->cdev.dev));
	aen_msg->length = data_size;

	data_size += sizeof(*aen_msg);

	total_size = nla_total_size(data_size);
	/* Add GENL_HDR to total_size */
	nla_genl_hdr_total_size =
		(total_size + (GENL_HDRLEN +
		((struct genl_family *)&pmcraid_event_family)->hdrsize)
		 + NLMSG_HDRLEN);
	skb = genlmsg_new(nla_genl_hdr_total_size, GFP_ATOMIC);


	if (!skb) {
		pmcraid_err("Failed to allocate aen data SKB of size: %x\n",
			     total_size);
		return -ENOMEM;
	}

	/* add the genetlink message header */
	msg_header = genlmsg_put(skb, 0, 0,
				 &pmcraid_event_family, 0,
				 PMCRAID_AEN_CMD_EVENT);
	if (!msg_header) {
		pmcraid_err("failed to copy command details\n");
		nlmsg_free(skb);
		return -ENOMEM;
	}

	result = nla_put(skb, PMCRAID_AEN_ATTR_EVENT, data_size, aen_msg);

	if (result) {
		pmcraid_err("failed to copy AEN attribute data\n");
		nlmsg_free(skb);
		return -EINVAL;
	}

	/* send genetlink multicast message to notify appplications */
	result = genlmsg_end(skb, msg_header);

	if (result < 0) {
		pmcraid_err("genlmsg_end failed\n");
		nlmsg_free(skb);
		return result;
	}

	result =
		genlmsg_multicast(skb, 0, pmcraid_event_family.id, GFP_ATOMIC);

	/* If there are no listeners, genlmsg_multicast may return non-zero
	 * value.
	 */
	if (result)
		pmcraid_info("error (%x) sending aen event message\n", result);
	return result;
}
