vrrp_script_handler(vector_t *strvec)
{
	if (!strvec)
		return;

	alloc_vrrp_script(strvec_slot(strvec, 1));
	script_user_set = false;
	remove_script = false;
}
