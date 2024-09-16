void xt_compat_lock(u_int8_t af)
{
	mutex_lock(&xt[af].compat_mutex);
}
