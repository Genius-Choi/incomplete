const char *string_of_NPError(int error)
{
  const char *str;

  switch ((NPError)error) {
#define _(VAL) case VAL: str = #VAL; break;
	_(NPERR_NO_ERROR);
	_(NPERR_GENERIC_ERROR);
	_(NPERR_INVALID_INSTANCE_ERROR);
	_(NPERR_INVALID_FUNCTABLE_ERROR);
	_(NPERR_MODULE_LOAD_FAILED_ERROR);
	_(NPERR_OUT_OF_MEMORY_ERROR);
	_(NPERR_INVALID_PLUGIN_ERROR);
	_(NPERR_INVALID_PLUGIN_DIR_ERROR);
	_(NPERR_INCOMPATIBLE_VERSION_ERROR);
	_(NPERR_INVALID_PARAM);
	_(NPERR_INVALID_URL);
	_(NPERR_FILE_NOT_FOUND);
	_(NPERR_NO_DATA);
	_(NPERR_STREAM_NOT_SEEKABLE);
#undef _
  default:
	str = "<unknown error>";
	break;
  }

  return str;
}
