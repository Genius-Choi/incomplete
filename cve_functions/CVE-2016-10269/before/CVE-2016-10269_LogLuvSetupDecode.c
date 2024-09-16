LogLuvSetupDecode(TIFF* tif)
{
	static const char module[] = "LogLuvSetupDecode";
	LogLuvState* sp = DecoderState(tif);
	TIFFDirectory* td = &tif->tif_dir;

	tif->tif_postdecode = _TIFFNoPostDecode;
	switch (td->td_photometric) {
	case PHOTOMETRIC_LOGLUV:
		if (!LogLuvInitState(tif))
			break;
		if (td->td_compression == COMPRESSION_SGILOG24) {
			tif->tif_decoderow = LogLuvDecode24;
			switch (sp->user_datafmt) {
			case SGILOGDATAFMT_FLOAT:
				sp->tfunc = Luv24toXYZ;  
				break;
			case SGILOGDATAFMT_16BIT:
				sp->tfunc = Luv24toLuv48;  
				break;
			case SGILOGDATAFMT_8BIT:
				sp->tfunc = Luv24toRGB;
				break;
			}
		} else {
			tif->tif_decoderow = LogLuvDecode32;
			switch (sp->user_datafmt) {
			case SGILOGDATAFMT_FLOAT:
				sp->tfunc = Luv32toXYZ;
				break;
			case SGILOGDATAFMT_16BIT:
				sp->tfunc = Luv32toLuv48;
				break;
			case SGILOGDATAFMT_8BIT:
				sp->tfunc = Luv32toRGB;
				break;
			}
		}
		return (1);
	case PHOTOMETRIC_LOGL:
		if (!LogL16InitState(tif))
			break;
		tif->tif_decoderow = LogL16Decode;
		switch (sp->user_datafmt) {
		case SGILOGDATAFMT_FLOAT:
			sp->tfunc = L16toY;
			break;
		case SGILOGDATAFMT_8BIT:
			sp->tfunc = L16toGry;
			break;
		}
		return (1);
	default:
		TIFFErrorExt(tif->tif_clientdata, module,
		    "Inappropriate photometric interpretation %d for SGILog compression; %s",
		    td->td_photometric, "must be either LogLUV or LogL");
		break;
	}
	return (0);
}
