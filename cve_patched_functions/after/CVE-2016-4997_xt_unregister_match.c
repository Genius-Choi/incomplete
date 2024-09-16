xt_unregister_match(struct xt_match *match)
{
	u_int8_t af = match->family;

	mutex_lock(&xt[af].mutex);
	list_del(&match->list);
	mutex_unlock(&xt[af].mutex);
}
