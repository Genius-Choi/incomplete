int yr_object_set_string(
    const char* value,
    size_t len,
    YR_OBJECT* object,
    const char* field,
    ...)
{
  YR_OBJECT_STRING* string_obj;

  va_list args;
  va_start(args, field);

  if (field != NULL)
    string_obj = (YR_OBJECT_STRING*) _yr_object_lookup(
        object, OBJECT_CREATE, field, args);
  else
    string_obj = (YR_OBJECT_STRING*) object;

  va_end(args);

  assert(string_obj != NULL);
  assert(string_obj->type == OBJECT_TYPE_STRING);

  if (string_obj->value != NULL)
    yr_free(string_obj->value);

  if (value != NULL)
  {
    string_obj->value = (SIZED_STRING*) yr_malloc(len + sizeof(SIZED_STRING));

    if (string_obj->value == NULL)
      return ERROR_INSUFFICIENT_MEMORY;

    string_obj->value->length = (uint32_t) len;
    string_obj->value->flags = 0;

    memcpy(string_obj->value->c_string, value, len);
    string_obj->value->c_string[len] = '\0';
  }
  else
  {
    string_obj->value = NULL;
  }

  return ERROR_SUCCESS;
}
