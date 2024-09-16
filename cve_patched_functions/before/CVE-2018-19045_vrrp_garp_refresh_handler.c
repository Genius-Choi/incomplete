vrrp_garp_refresh_handler(vector_t *strvec)
{
        unsigned refresh;

        if (!read_unsigned_strvec(strvec, 1, &refresh, 0, UINT_MAX, true)) {
                report_config_error(CONFIG_GENERAL_ERROR, "Invalid vrrp_garp_master_refresh '%s' - ignoring", FMT_STR_VSLOT(strvec, 1));
                global_data->vrrp_garp_refresh.tv_sec = 0;
        }
        else
		global_data->vrrp_garp_refresh.tv_sec = refresh;

        global_data->vrrp_garp_refresh.tv_usec = 0;
}
