Perl_new_warnings_bitfield(pTHX_ STRLEN *buffer, const char *const bits,
			   STRLEN size) {
    const MEM_SIZE len_wanted =
	sizeof(STRLEN) + (size > WARNsize ? size : WARNsize);
    PERL_UNUSED_CONTEXT;
    PERL_ARGS_ASSERT_NEW_WARNINGS_BITFIELD;

    buffer = (STRLEN*)
	(specialWARN(buffer) ?
	 PerlMemShared_malloc(len_wanted) :
	 PerlMemShared_realloc(buffer, len_wanted));
    buffer[0] = size;
    Copy(bits, (buffer + 1), size, char);
    if (size < WARNsize)
	Zero((char *)(buffer + 1) + size, WARNsize - size, char);
    return buffer;
}
