wkbConvGeometryToShape(wkbObj *w, shapeObj *shape)
{
  int wkbtype = wkbType(w); /* Peak at the type number */

  switch(wkbtype) {
      /* Recurse into anonymous collections */
    case WKB_GEOMETRYCOLLECTION:
      return wkbConvCollectionToShape(w, shape);
      /* Handle area types */
    case WKB_POLYGON:
      return wkbConvPolygonToShape(w, shape);
    case WKB_MULTIPOLYGON:
      return wkbConvCollectionToShape(w, shape);
    case WKB_CURVEPOLYGON:
      return wkbConvCurvePolygonToShape(w, shape);
    case WKB_MULTISURFACE:
      return wkbConvCollectionToShape(w, shape);
  }

  /* We can't convert any of the following types into polygons */
  if ( shape->type == MS_SHAPE_POLYGON ) return MS_FAILURE;

  /* Handle linear types */
  switch(wkbtype) {
    case WKB_LINESTRING:
      return wkbConvLineStringToShape(w, shape);
    case WKB_CIRCULARSTRING:
      return wkbConvCircularStringToShape(w, shape);
    case WKB_COMPOUNDCURVE:
      return wkbConvCompoundCurveToShape(w, shape);
    case WKB_MULTILINESTRING:
      return wkbConvCollectionToShape(w, shape);
    case WKB_MULTICURVE:
      return wkbConvCollectionToShape(w, shape);
  }

  /* We can't convert any of the following types into lines */
  if ( shape->type == MS_SHAPE_LINE ) return MS_FAILURE;

  /* Handle point types */
  switch(wkbtype) {
    case WKB_POINT:
      return wkbConvPointToShape(w, shape);
    case WKB_MULTIPOINT:
      return wkbConvCollectionToShape(w, shape);
  }

  /* This is a WKB type we don't know about! */
  return MS_FAILURE;
}
