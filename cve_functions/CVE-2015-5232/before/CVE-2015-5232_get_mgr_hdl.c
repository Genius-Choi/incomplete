get_mgr_hdl
(
	IN      p_fm_config_conx_hdlt       hdl,
	IN      fm_mgr_type_t               mgr
)
{
	switch ( mgr )
	{
		case FM_MGR_SM:
			return hdl->sm_hdl;
		case FM_MGR_PM:
			return hdl->pm_hdl;
		case FM_MGR_FE:
			return hdl->fe_hdl;
		default:
			return NULL;
	}

	return NULL;

}
