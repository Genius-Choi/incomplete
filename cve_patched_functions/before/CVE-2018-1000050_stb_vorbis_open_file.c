stb_vorbis * stb_vorbis_open_file(FILE *file, int close_on_free, int *error, const stb_vorbis_alloc *alloc)
{
   unsigned int len, start;
   start = (unsigned int) ftell(file);
   fseek(file, 0, SEEK_END);
   len = (unsigned int) (ftell(file) - start);
   fseek(file, start, SEEK_SET);
   return stb_vorbis_open_file_section(file, close_on_free, error, alloc, len);
}
