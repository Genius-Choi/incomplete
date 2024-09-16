static struct dcb_app_type *dcb_app_lookup(const struct dcb_app *app,
					   int ifindex, int prio)
{
	struct dcb_app_type *itr;

	list_for_each_entry(itr, &dcb_app_list, list) {
		if (itr->app.selector == app->selector &&
		    itr->app.protocol == app->protocol &&
		    itr->ifindex == ifindex &&
		    (!prio || itr->app.priority == prio))
			return itr;
	}

	return NULL;
}
