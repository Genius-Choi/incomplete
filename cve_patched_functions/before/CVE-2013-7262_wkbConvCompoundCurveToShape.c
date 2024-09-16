wkbConvCompoundCurveToShape(wkbObj *w, shapeObj *shape)
{
  int npoints = 0;
  int type, ncomponents, i, j;
  lineObj *line;
  shapeObj shapebuf;

  /*endian = */wkbReadChar(w);
  type = wkbTypeMap(w,wkbReadInt(w));

  /* Init our shape buffer */
  msInitShape(&shapebuf);

  if( type != WKB_COMPOUNDCURVE ) return MS_FAILURE;

  /* How many components in the compound curve? */
  ncomponents = wkbReadInt(w);

  /* We'll load each component onto a line in a shape */
  for( i = 0; i < ncomponents; i++ )
    wkbConvGeometryToShape(w, &shapebuf);

  /* Do nothing on empty */
  if ( shapebuf.numlines == 0 )
    return MS_FAILURE;

  /* Count the total number of points */
  for( i = 0; i < shapebuf.numlines; i++ )
    npoints += shapebuf.line[i].numpoints;

  /* Do nothing on empty */
  if ( npoints == 0 )
    return MS_FAILURE;

  /* Allocate space for the new line */
  line = msSmallMalloc(sizeof(lineObj));
  line->numpoints = npoints;
  line->point = msSmallMalloc(sizeof(pointObj) * npoints);

  /* Copy in the points */
  npoints = 0;
  for ( i = 0; i < shapebuf.numlines; i++ ) {
    for ( j = 0; j < shapebuf.line[i].numpoints; j++ ) {
      /* Don't add a start point that duplicates an endpoint */
      if( j == 0 && i > 0 &&
          memcmp(&(line->point[npoints - 1]),&(shapebuf.line[i].point[j]),sizeof(pointObj)) == 0 ) {
        continue;
      }
      line->point[npoints++] = shapebuf.line[i].point[j];
    }
  }
  line->numpoints = npoints;

  /* Clean up */
  msFreeShape(&shapebuf);

  /* Fill in the lineObj */
  msAddLineDirectly(shape, line);

  return MS_SUCCESS;
}
