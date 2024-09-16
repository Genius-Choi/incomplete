static GF_Err gf_isom_avc_config_update_ex(GF_ISOFile *the_file, u32 trackNumber, u32 DescriptionIndex, GF_AVCConfig *cfg, u32 op_type)
{
	GF_TrackBox *trak;
	GF_Err e;
	GF_MPEGVisualSampleEntryBox *entry;

	e = CanAccessMovie(the_file, GF_ISOM_OPEN_WRITE);
	if (e) return e;
	trak = gf_isom_get_track_from_file(the_file, trackNumber);
	if (!trak || !trak->Media || !DescriptionIndex) return GF_BAD_PARAM;
	entry = (GF_MPEGVisualSampleEntryBox *)gf_list_get(trak->Media->information->sampleTable->SampleDescription->other_boxes, DescriptionIndex-1);
	if (!entry) return GF_BAD_PARAM;
	switch (entry->type) {
	case GF_ISOM_BOX_TYPE_AVC1:
	case GF_ISOM_BOX_TYPE_AVC2:
	case GF_ISOM_BOX_TYPE_AVC3:
	case GF_ISOM_BOX_TYPE_AVC4:
	case GF_ISOM_BOX_TYPE_SVC1:
	case GF_ISOM_BOX_TYPE_MVC1:
		break;
	default:
		return GF_BAD_PARAM;
	}

	switch (op_type) {
	/*AVCC replacement*/
	case 0:
		if (!cfg) return GF_BAD_PARAM;
		if (!entry->avc_config) entry->avc_config = (GF_AVCConfigurationBox*)gf_isom_box_new(GF_ISOM_BOX_TYPE_AVCC);
		if (entry->avc_config->config) gf_odf_avc_cfg_del(entry->avc_config->config);
		entry->avc_config->config = AVC_DuplicateConfig(cfg);
		entry->type = GF_ISOM_BOX_TYPE_AVC1;
		break;
	/*SVCC replacement*/
	case 1:
		if (!cfg) return GF_BAD_PARAM;
		if (!entry->svc_config) entry->svc_config = (GF_AVCConfigurationBox*)gf_isom_box_new(GF_ISOM_BOX_TYPE_SVCC);
		if (entry->svc_config->config) gf_odf_avc_cfg_del(entry->svc_config->config);
		entry->svc_config->config = AVC_DuplicateConfig(cfg);
		entry->type = GF_ISOM_BOX_TYPE_AVC1;
		break;
	/*SVCC replacement and AVC removal*/
	case 2:
		if (!cfg) return GF_BAD_PARAM;
		if (entry->avc_config) {
			gf_isom_box_del((GF_Box*)entry->avc_config);
			entry->avc_config = NULL;
		}
		if (!entry->svc_config) entry->svc_config = (GF_AVCConfigurationBox*)gf_isom_box_new(GF_ISOM_BOX_TYPE_SVCC);
		if (entry->svc_config->config) gf_odf_avc_cfg_del(entry->svc_config->config);
		entry->svc_config->config = AVC_DuplicateConfig(cfg);
		entry->type = GF_ISOM_BOX_TYPE_SVC1;
		break;
	/*AVCC removal and switch to avc3*/
	case 3:
		if (!entry->avc_config || !entry->avc_config->config)
			return GF_BAD_PARAM;

		if (entry->svc_config) {
			gf_isom_box_del((GF_Box*)entry->svc_config);
			entry->svc_config = NULL;
		}
		if (entry->mvc_config) {
			gf_isom_box_del((GF_Box*)entry->mvc_config);
			entry->mvc_config = NULL;
		}

		while (gf_list_count(entry->avc_config->config->sequenceParameterSets)) {
			GF_AVCConfigSlot *sl = (GF_AVCConfigSlot*)gf_list_get(entry->avc_config->config->sequenceParameterSets, 0);
			gf_list_rem(entry->avc_config->config->sequenceParameterSets, 0);
			if (sl->data) gf_free(sl->data);
			gf_free(sl);
		}

		while (gf_list_count(entry->avc_config->config->pictureParameterSets)) {
			GF_AVCConfigSlot *sl = (GF_AVCConfigSlot*)gf_list_get(entry->avc_config->config->pictureParameterSets, 0);
			gf_list_rem(entry->avc_config->config->pictureParameterSets, 0);
			if (sl->data) gf_free(sl->data);
			gf_free(sl);
		}

		if (entry->type == GF_ISOM_BOX_TYPE_AVC1)
			entry->type = GF_ISOM_BOX_TYPE_AVC3;
		else if (entry->type == GF_ISOM_BOX_TYPE_AVC2)
			entry->type = GF_ISOM_BOX_TYPE_AVC4;
		break;
	/*MVCC replacement*/
	case 4:
		if (!cfg) return GF_BAD_PARAM;
		if (!entry->mvc_config) entry->mvc_config = (GF_AVCConfigurationBox*)gf_isom_box_new(GF_ISOM_BOX_TYPE_MVCC);
		if (entry->mvc_config->config) gf_odf_avc_cfg_del(entry->mvc_config->config);
		entry->mvc_config->config = AVC_DuplicateConfig(cfg);
		entry->type = GF_ISOM_BOX_TYPE_AVC1;
		break;
	/*MVCC replacement and AVC removal*/
	case 5:
		if (!cfg) return GF_BAD_PARAM;
		if (entry->avc_config) {
			gf_isom_box_del((GF_Box*)entry->avc_config);
			entry->avc_config = NULL;
		}
		if (!entry->mvc_config) entry->mvc_config = (GF_AVCConfigurationBox*)gf_isom_box_new(GF_ISOM_BOX_TYPE_MVCC);
		if (entry->mvc_config->config) gf_odf_avc_cfg_del(entry->mvc_config->config);
		entry->mvc_config->config = AVC_DuplicateConfig(cfg);
		entry->type = GF_ISOM_BOX_TYPE_MVC1;
		break;
	}
	AVC_RewriteESDescriptor(entry);
	return GF_OK;
}
