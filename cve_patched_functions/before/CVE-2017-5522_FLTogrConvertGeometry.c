int FLTogrConvertGeometry(OGRGeometryH hGeometry, shapeObj *psShape,
                          OGRwkbGeometryType nType)
{
  return msOGRGeometryToShape(hGeometry, psShape, nType);
}
