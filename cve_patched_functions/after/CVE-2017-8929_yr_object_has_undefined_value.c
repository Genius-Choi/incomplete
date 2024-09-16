int yr_object_has_undefined_value(
    YR_OBJECT* object,
    const char* field,
    ...)
{
  YR_OBJECT* field_obj;

  va_list args;
  va_start(args, field);

  if (field != NULL)
    field_obj = _yr_object_lookup(object, 0, field, args);
  else
    field_obj = object;

  va_end(args);

  if (field_obj == NULL)
    return TRUE;

  switch(field_obj->type)
  {
    case OBJECT_TYPE_FLOAT:
      return isnan(((YR_OBJECT_DOUBLE*) field_obj)->value);
    case OBJECT_TYPE_STRING:
      return ((YR_OBJECT_STRING*) field_obj)->value == NULL;
    case OBJECT_TYPE_INTEGER:
      return ((YR_OBJECT_INTEGER*) field_obj)->value == UNDEFINED;
  }

  return FALSE;
}
