wkbConvLineStringToShape(wkbObj *w, shapeObj *shape)
{
  int type;
  lineObj line;

  /*endian = */wkbReadChar(w);
  type = wkbTypeMap(w,wkbReadInt(w));

  if( type != WKB_LINESTRING ) return MS_FAILURE;

  wkbReadLine(w,&line);
  msAddLineDirectly(shape, &line);

  return MS_SUCCESS;
}
