void ndp_msgrcv_handler_unregister(struct ndp *ndp, ndp_msgrcv_handler_func_t func,
				   enum ndp_msg_type msg_type, uint32_t ifindex,
				   void *priv)
{
	struct ndp_msgrcv_handler_item *handler_item;

	handler_item = ndp_find_msgrcv_handler_item(ndp, func, msg_type,
						    ifindex, priv);
	if (!handler_item)
		return;
	list_del(&handler_item->list);
	free(handler_item);
}
