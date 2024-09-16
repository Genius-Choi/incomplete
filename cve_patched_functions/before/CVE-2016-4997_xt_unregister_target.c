xt_unregister_target(struct xt_target *target)
{
	u_int8_t af = target->family;

	mutex_lock(&xt[af].mutex);
	list_del(&target->list);
	mutex_unlock(&xt[af].mutex);
}
