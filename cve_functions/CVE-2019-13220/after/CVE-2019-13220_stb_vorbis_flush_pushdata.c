void stb_vorbis_flush_pushdata(stb_vorbis *f)
{
   f->previous_length = 0;
   f->page_crc_tests  = 0;
   f->discard_samples_deferred = 0;
   f->current_loc_valid = FALSE;
   f->first_decode = FALSE;
   f->samples_output = 0;
   f->channel_buffer_start = 0;
   f->channel_buffer_end = 0;
}
