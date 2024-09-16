static int parse_audio_processing_unit(struct mixer_build *state, int unitid,
				       void *raw_desc)
{
	return build_audio_procunit(state, unitid, raw_desc,
				    procunits, "Processing Unit");
}
