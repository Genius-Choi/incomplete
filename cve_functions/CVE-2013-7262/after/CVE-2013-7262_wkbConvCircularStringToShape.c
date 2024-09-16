wkbConvCircularStringToShape(wkbObj *w, shapeObj *shape)
{
  int type;
  lineObj line = {0, NULL};

  /*endian = */wkbReadChar(w);
  type = wkbTypeMap(w,wkbReadInt(w));

  if( type != WKB_CIRCULARSTRING ) return MS_FAILURE;

  /* Stroke the string into a point array */
  if ( arcStrokeCircularString(w, SEGMENT_ANGLE, &line) == MS_FAILURE ) {
    if(line.point) free(line.point);
    return MS_FAILURE;
  }

  /* Fill in the lineObj */
  if ( line.numpoints > 0 ) {
    msAddLine(shape, &line);
    if(line.point) free(line.point);
  }

  return MS_SUCCESS;
}
