wkbTypeMap(wkbObj *w, int type)
{
  if ( type < WKB_TYPE_COUNT )
    return w->typemap[type];
  else
    return 0;
}
