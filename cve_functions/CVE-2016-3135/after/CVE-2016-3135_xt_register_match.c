int xt_register_match(struct xt_match *match)
{
	u_int8_t af = match->family;

	mutex_lock(&xt[af].mutex);
	list_add(&match->list, &xt[af].match);
	mutex_unlock(&xt[af].mutex);
	return 0;
}
