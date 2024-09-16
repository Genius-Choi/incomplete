writeSingleSection(TIFF *in, TIFF *out, struct image_data *image,
                   struct dump_opts *dump, uint32 width, uint32 length,
                   double hres, double vres,
                   unsigned char *sect_buff)
  {
  uint16 bps, spp;
  uint16 input_compression, input_photometric;
  uint16 input_planar;
  struct cpTag* p;

  /*  Calling this seems to reset the compression mode on the TIFF *in file.
  TIFFGetField(in, TIFFTAG_JPEGCOLORMODE, &input_jpeg_colormode);
  */
  input_compression = image->compression;
  input_photometric = image->photometric;

  spp = image->spp;
  bps = image->bps;
  TIFFSetField(out, TIFFTAG_IMAGEWIDTH, width);
  TIFFSetField(out, TIFFTAG_IMAGELENGTH, length);
  TIFFSetField(out, TIFFTAG_BITSPERSAMPLE, bps);
  TIFFSetField(out, TIFFTAG_SAMPLESPERPIXEL, spp);

#ifdef DEBUG2
  TIFFError("writeSingleSection", "Input compression: %s",
	    (input_compression == COMPRESSION_OJPEG) ? "Old Jpeg" :
	    ((input_compression == COMPRESSION_JPEG) ?  "New Jpeg" : "Non Jpeg"));
#endif
  /* This is the global variable compression which is set 
   * if the user has specified a command line option for 
   * a compression option.  Should be passed around in one
   * of the parameters instead of as a global. If no user
   * option specified it will still be (uint16) -1. */
  if (compression != (uint16)-1)
    TIFFSetField(out, TIFFTAG_COMPRESSION, compression);
  else
    { /* OJPEG is no longer supported for writing so upgrade to JPEG */
    if (input_compression == COMPRESSION_OJPEG)
      {
      compression = COMPRESSION_JPEG;
      jpegcolormode = JPEGCOLORMODE_RAW;
      TIFFSetField(out, TIFFTAG_COMPRESSION, COMPRESSION_JPEG);
      }
    else /* Use the compression from the input file */
      CopyField(TIFFTAG_COMPRESSION, compression);
    }

  if (compression == COMPRESSION_JPEG)
    {
    if ((input_photometric == PHOTOMETRIC_PALETTE) ||  /* color map indexed */
        (input_photometric == PHOTOMETRIC_MASK))       /* holdout mask */
      {
      TIFFError ("writeSingleSection",
                 "JPEG compression cannot be used with %s image data",
		 (input_photometric == PHOTOMETRIC_PALETTE) ?
                 "palette" : "mask");
      return (-1);
      }
    if ((input_photometric == PHOTOMETRIC_RGB) &&
	(jpegcolormode == JPEGCOLORMODE_RGB))
      TIFFSetField(out, TIFFTAG_PHOTOMETRIC, PHOTOMETRIC_YCBCR);
    else
	TIFFSetField(out, TIFFTAG_PHOTOMETRIC, input_photometric);
    }
  else
    {
    if (compression == COMPRESSION_SGILOG || compression == COMPRESSION_SGILOG24)
      TIFFSetField(out, TIFFTAG_PHOTOMETRIC, spp == 1 ?
			PHOTOMETRIC_LOGL : PHOTOMETRIC_LOGLUV);
    else
      TIFFSetField(out, TIFFTAG_PHOTOMETRIC, image->photometric);
    }

#ifdef DEBUG2
  TIFFError("writeSingleSection", "Input photometric: %s",
	    (input_photometric == PHOTOMETRIC_RGB) ? "RGB" :
	    ((input_photometric == PHOTOMETRIC_YCBCR) ?  "YCbCr" : "Not RGB or YCbCr"));
#endif

  if (((input_photometric == PHOTOMETRIC_LOGL) ||
       (input_photometric ==  PHOTOMETRIC_LOGLUV)) &&
      ((compression != COMPRESSION_SGILOG) && 
       (compression != COMPRESSION_SGILOG24)))
    {
    TIFFError("writeSingleSection",
              "LogL and LogLuv source data require SGI_LOG or SGI_LOG24 compression");
    return (-1);
    }

  if (fillorder != 0)
    TIFFSetField(out, TIFFTAG_FILLORDER, fillorder);
  else
    CopyTag(TIFFTAG_FILLORDER, 1, TIFF_SHORT);

  /* The loadimage function reads input orientation and sets
   * image->orientation. The correct_image_orientation function
   * applies the required rotation and mirror operations to 
   * present the data in TOPLEFT orientation and updates 
   * image->orientation if any transforms are performed, 
   * as per EXIF standard.
   */
  TIFFSetField(out, TIFFTAG_ORIENTATION, image->orientation);

  /*
   * Choose tiles/strip for the output image according to
   * the command line arguments (-tiles, -strips) and the
   * structure of the input image.
   */
  if (outtiled == -1)
    outtiled = TIFFIsTiled(in);
  if (outtiled) {
    /*
     * Setup output file's tile width&height.  If either
     * is not specified, use either the value from the
     * input image or, if nothing is defined, use the
     * library default.
     */
    if (tilewidth == (uint32) 0)
      TIFFGetField(in, TIFFTAG_TILEWIDTH, &tilewidth);
    if (tilelength == (uint32) 0)
      TIFFGetField(in, TIFFTAG_TILELENGTH, &tilelength);

    if (tilewidth == 0 || tilelength == 0)
      TIFFDefaultTileSize(out, &tilewidth, &tilelength);
    TIFFDefaultTileSize(out, &tilewidth, &tilelength);
    TIFFSetField(out, TIFFTAG_TILEWIDTH, tilewidth);
    TIFFSetField(out, TIFFTAG_TILELENGTH, tilelength);
    } else {
       /*
	* RowsPerStrip is left unspecified: use either the
	* value from the input image or, if nothing is defined,
	* use the library default.
	*/
	if (rowsperstrip == (uint32) 0)
          {
	  if (!TIFFGetField(in, TIFFTAG_ROWSPERSTRIP, &rowsperstrip))
	    rowsperstrip = TIFFDefaultStripSize(out, rowsperstrip);
          if (compression != COMPRESSION_JPEG)
            {
  	    if (rowsperstrip > length)
	      rowsperstrip = length;
	    }
	  }
	else 
          if (rowsperstrip == (uint32) -1)
	    rowsperstrip = length;
	TIFFSetField(out, TIFFTAG_ROWSPERSTRIP, rowsperstrip);
	}

  TIFFGetFieldDefaulted(in, TIFFTAG_PLANARCONFIG, &input_planar);
  if (config != (uint16) -1)
    TIFFSetField(out, TIFFTAG_PLANARCONFIG, config);
  else
    CopyField(TIFFTAG_PLANARCONFIG, config);
  if (spp <= 4)
    CopyTag(TIFFTAG_TRANSFERFUNCTION, 4, TIFF_SHORT);
  CopyTag(TIFFTAG_COLORMAP, 4, TIFF_SHORT);

/* SMinSampleValue & SMaxSampleValue */
  switch (compression) {
    /* These are references to GLOBAL variables set by defaults
     * and /or the compression flag
     */
    case COMPRESSION_JPEG:
         if (((bps % 8) == 0) || ((bps % 12) == 0))
	   {
           TIFFSetField(out, TIFFTAG_JPEGQUALITY, quality);
	   TIFFSetField(out, TIFFTAG_JPEGCOLORMODE, JPEGCOLORMODE_RGB);
           }
         else
           {
	   TIFFError("writeSingleSection",
                     "JPEG compression requires 8 or 12 bits per sample");
           return (-1);
           }
	 break;
   case COMPRESSION_LZW:
   case COMPRESSION_ADOBE_DEFLATE:
   case COMPRESSION_DEFLATE:
	if (predictor != (uint16)-1)
          TIFFSetField(out, TIFFTAG_PREDICTOR, predictor);
	else
	  CopyField(TIFFTAG_PREDICTOR, predictor);
	break;
   case COMPRESSION_CCITTFAX3:
   case COMPRESSION_CCITTFAX4:
	if (compression == COMPRESSION_CCITTFAX3) {
          if (g3opts != (uint32) -1)
	    TIFFSetField(out, TIFFTAG_GROUP3OPTIONS, g3opts);
	  else
	    CopyField(TIFFTAG_GROUP3OPTIONS, g3opts);
	} else {
	    CopyTag(TIFFTAG_GROUP4OPTIONS, 1, TIFF_LONG);
        }
        CopyTag(TIFFTAG_BADFAXLINES, 1, TIFF_LONG);
        CopyTag(TIFFTAG_CLEANFAXDATA, 1, TIFF_LONG);
        CopyTag(TIFFTAG_CONSECUTIVEBADFAXLINES, 1, TIFF_LONG);
        CopyTag(TIFFTAG_FAXRECVPARAMS, 1, TIFF_LONG);
        CopyTag(TIFFTAG_FAXRECVTIME, 1, TIFF_LONG);
        CopyTag(TIFFTAG_FAXSUBADDRESS, 1, TIFF_ASCII);
	break;
   }
   { uint32 len32;
     void** data;
     if (TIFFGetField(in, TIFFTAG_ICCPROFILE, &len32, &data))
       TIFFSetField(out, TIFFTAG_ICCPROFILE, len32, data);
   }
   { uint16 ninks;
     const char* inknames;
     if (TIFFGetField(in, TIFFTAG_NUMBEROFINKS, &ninks)) {
       TIFFSetField(out, TIFFTAG_NUMBEROFINKS, ninks);
       if (TIFFGetField(in, TIFFTAG_INKNAMES, &inknames)) {
	 int inknameslen = strlen(inknames) + 1;
	 const char* cp = inknames;
	 while (ninks > 1) {
	   cp = strchr(cp, '\0');
	   if (cp) {
	     cp++;
	     inknameslen += (strlen(cp) + 1);
	   }
	   ninks--;
         }
	 TIFFSetField(out, TIFFTAG_INKNAMES, inknameslen, inknames);
       }
     }
   }
   {
   unsigned short pg0, pg1;
   if (TIFFGetField(in, TIFFTAG_PAGENUMBER, &pg0, &pg1)) {
     if (pageNum < 0) /* only one input file */
	TIFFSetField(out, TIFFTAG_PAGENUMBER, pg0, pg1);
     else 
	TIFFSetField(out, TIFFTAG_PAGENUMBER, pageNum++, 0);
     }
   }

  for (p = tags; p < &tags[NTAGS]; p++)
		CopyTag(p->tag, p->count, p->type);

  /* Update these since they are overwritten from input res by loop above */
  TIFFSetField(out, TIFFTAG_XRESOLUTION, (float)hres);
  TIFFSetField(out, TIFFTAG_YRESOLUTION, (float)vres);

  /* Compute the tile or strip dimensions and write to disk */
  if (outtiled)
    {
    if (config == PLANARCONFIG_CONTIG)
      writeBufferToContigTiles (out, sect_buff, length, width, spp, dump);
    else
      writeBufferToSeparateTiles (out, sect_buff, length, width, spp, dump);
    }
  else
    {
    if (config == PLANARCONFIG_CONTIG)
      writeBufferToContigStrips (out, sect_buff, length);
    else
      writeBufferToSeparateStrips(out, sect_buff, length, width, spp, dump);
    }

  if (!TIFFWriteDirectory(out))
    {
    TIFFClose(out);
    return (-1);
    }

  return (0);
  } /* end writeSingleSection */
