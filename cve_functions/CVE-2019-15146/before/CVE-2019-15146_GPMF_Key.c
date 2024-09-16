uint32_t GPMF_Key(GPMF_stream *ms)
{
	if (ms)
	{
		uint32_t key = ms->buffer[ms->pos];
		return key;
	}
	return 0;
}
