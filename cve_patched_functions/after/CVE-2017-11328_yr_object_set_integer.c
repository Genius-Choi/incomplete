int yr_object_set_integer(
    int64_t value,
    YR_OBJECT* object,
    const char* field,
    ...)
{
  YR_OBJECT* integer_obj;

  va_list args;
  va_start(args, field);

  if (field != NULL)
    integer_obj = _yr_object_lookup(object, OBJECT_CREATE, field, args);
  else
    integer_obj = object;

  va_end(args);

  assert(integer_obj != NULL);
  assert(integer_obj->type == OBJECT_TYPE_INTEGER);

  integer_obj->value.i = value;

  return ERROR_SUCCESS;
}
