vrrp_promote_secondaries_handler(__attribute__((unused)) vector_t *strvec)
{
	vrrp_t *vrrp = LIST_TAIL_DATA(vrrp_data->vrrp);

	vrrp->promote_secondaries = true;
}
