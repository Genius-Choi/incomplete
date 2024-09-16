vrrp_tfile_file_handler(vector_t *strvec)
{
	vrrp_tracked_file_t *tfile = LIST_TAIL_DATA(vrrp_data->vrrp_track_files);
	if (tfile->file_path) {
		report_config_error(CONFIG_GENERAL_ERROR, "File already set for track file %s - ignoring %s", tfile->fname, FMT_STR_VSLOT(strvec, 1));
		return;
	}
	tfile->file_path = set_value(strvec);
}
