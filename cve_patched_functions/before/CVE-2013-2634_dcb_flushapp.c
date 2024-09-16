static void dcb_flushapp(void)
{
	struct dcb_app_type *app;
	struct dcb_app_type *tmp;

	spin_lock(&dcb_lock);
	list_for_each_entry_safe(app, tmp, &dcb_app_list, list) {
		list_del(&app->list);
		kfree(app);
	}
	spin_unlock(&dcb_lock);
}
