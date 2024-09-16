void hv_kvp_deinit(void)
{
	cn_del_callback(&kvp_id);
	cancel_delayed_work_sync(&kvp_work);
	cancel_work_sync(&kvp_sendkey_work);
}
