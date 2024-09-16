static inline wchar_t vfat_replace_char(wchar_t w)
{
	return (w == '[') || (w == ']') || (w == ';') || (w == ',')
	    || (w == '+') || (w == '=');
}
