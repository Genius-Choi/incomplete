static int ndp_call_handlers(struct ndp *ndp, struct ndp_msg *msg)
{
	struct ndp_msgrcv_handler_item *handler_item;
	int err;

	list_for_each_node_entry(handler_item,
				 &ndp->msgrcv_handler_list, list) {
		if (handler_item->msg_type != NDP_MSG_ALL &&
		    handler_item->msg_type != ndp_msg_type(msg))
			continue;
		if (handler_item->ifindex &&
		    handler_item->ifindex != msg->ifindex)
			continue;
		err = handler_item->func(ndp, msg, handler_item->priv);
		if (err)
			return err;
	}
	return 0;
}
