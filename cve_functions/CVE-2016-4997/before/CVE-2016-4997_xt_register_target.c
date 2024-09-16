int xt_register_target(struct xt_target *target)
{
	u_int8_t af = target->family;

	mutex_lock(&xt[af].mutex);
	list_add(&target->list, &xt[af].target);
	mutex_unlock(&xt[af].mutex);
	return 0;
}
