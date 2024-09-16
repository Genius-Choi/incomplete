int stb_vorbis_seek_start(stb_vorbis *f)
{
   if (IS_PUSH_MODE(f)) { return error(f, VORBIS_invalid_api_mixing); }
   set_file_offset(f, f->first_audio_page_offset);
   f->previous_length = 0;
   f->first_decode = TRUE;
   f->next_seg = -1;
   return vorbis_pump_first_frame(f);
}
