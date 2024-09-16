vrrp_vscript_init_fail_handler(__attribute__((unused)) vector_t *strvec)
{
	vrrp_script_t *vscript = LIST_TAIL_DATA(vrrp_data->vrrp_script);
	vscript->init_state = SCRIPT_INIT_STATE_FAILED;
}
