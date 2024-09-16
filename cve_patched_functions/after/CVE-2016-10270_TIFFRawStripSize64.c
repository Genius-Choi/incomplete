TIFFRawStripSize64(TIFF* tif, uint32 strip)
{
	static const char module[] = "TIFFRawStripSize64";
	TIFFDirectory* td = &tif->tif_dir;
	uint64 bytecount = td->td_stripbytecount[strip];

	if (bytecount == 0)
	{
#if defined(__WIN32__) && (defined(_MSC_VER) || defined(__MINGW32__))
		TIFFErrorExt(tif->tif_clientdata, module,
			     "%I64u: Invalid strip byte count, strip %lu",
			     (unsigned __int64) bytecount,
			     (unsigned long) strip);
#else
		TIFFErrorExt(tif->tif_clientdata, module,
			     "%llu: Invalid strip byte count, strip %lu",
			     (unsigned long long) bytecount,
			     (unsigned long) strip);
#endif
		bytecount = (uint64) -1;
	}

	return bytecount;
}
