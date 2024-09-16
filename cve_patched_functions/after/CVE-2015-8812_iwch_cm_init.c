int __init iwch_cm_init(void)
{
	skb_queue_head_init(&rxq);

	workq = create_singlethread_workqueue("iw_cxgb3");
	if (!workq)
		return -ENOMEM;

	return 0;
}
