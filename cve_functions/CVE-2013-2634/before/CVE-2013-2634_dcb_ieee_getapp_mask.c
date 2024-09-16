u8 dcb_ieee_getapp_mask(struct net_device *dev, struct dcb_app *app)
{
	struct dcb_app_type *itr;
	u8 prio = 0;

	spin_lock(&dcb_lock);
	if ((itr = dcb_app_lookup(app, dev->ifindex, 0)))
		prio |= 1 << itr->app.priority;
	spin_unlock(&dcb_lock);

	return prio;
}
