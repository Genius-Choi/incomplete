vrrp_tfile_weight_handler(vector_t *strvec)
{
	int weight;
	vrrp_tracked_file_t *tfile = LIST_TAIL_DATA(vrrp_data->vrrp_track_files);

	if (vector_size(strvec) < 2) {
		report_config_error(CONFIG_GENERAL_ERROR, "No weight specified for track file %s - ignoring", tfile->fname);
		return;
	}
	if (tfile->weight != 1) {
		report_config_error(CONFIG_GENERAL_ERROR, "Weight already set for track file %s - ignoring %s", tfile->fname, FMT_STR_VSLOT(strvec, 1));
		return;
	}

	if (!read_int_strvec(strvec, 1, &weight, -254, 254, true)) {
		report_config_error(CONFIG_GENERAL_ERROR, "Weight (%s) for vrrp_track_file %s must be between "
				 "[-254..254] inclusive. Ignoring...", FMT_STR_VSLOT(strvec, 1), tfile->fname);
		weight = 1;
	}

	tfile->weight = weight;
}
