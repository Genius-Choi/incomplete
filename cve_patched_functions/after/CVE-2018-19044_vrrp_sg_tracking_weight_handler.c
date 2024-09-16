vrrp_sg_tracking_weight_handler(__attribute__((unused)) vector_t *strvec)
{
	vrrp_sgroup_t *vgroup = LIST_TAIL_DATA(vrrp_data->vrrp_sync_group);
	vgroup->sgroup_tracking_weight = true;
}
