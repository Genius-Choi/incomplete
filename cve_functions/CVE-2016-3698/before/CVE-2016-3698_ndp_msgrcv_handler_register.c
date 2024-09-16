int ndp_msgrcv_handler_register(struct ndp *ndp, ndp_msgrcv_handler_func_t func,
				enum ndp_msg_type msg_type, uint32_t ifindex,
				void *priv)
{
	struct ndp_msgrcv_handler_item *handler_item;

	if (ndp_find_msgrcv_handler_item(ndp, func, msg_type,
					 ifindex, priv))
		return -EEXIST;
	if (!func)
		return -EINVAL;
	handler_item = malloc(sizeof(*handler_item));
	if (!handler_item)
		return -ENOMEM;
	handler_item->func = func;
	handler_item->msg_type = msg_type;
	handler_item->ifindex = ifindex;
	handler_item->priv = priv;
	list_add_tail(&ndp->msgrcv_handler_list, &handler_item->list);
	return 0;
}
