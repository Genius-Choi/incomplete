void yr_object_destroy(
    YR_OBJECT* object)
{
  YR_STRUCTURE_MEMBER* member;
  YR_STRUCTURE_MEMBER* next_member;
  YR_ARRAY_ITEMS* array_items;
  YR_DICTIONARY_ITEMS* dict_items;

  SIZED_STRING* str;
  int i;

  if (object == NULL)
    return;

  switch(object->type)
  {
    case OBJECT_TYPE_STRUCTURE:
      member = ((YR_OBJECT_STRUCTURE*) object)->members;

      while (member != NULL)
      {
        next_member = member->next;
        yr_object_destroy(member->object);
        yr_free(member);
        member = next_member;
      }
      break;

    case OBJECT_TYPE_STRING:
      str = ((YR_OBJECT_STRING*) object)->value;
      if (str != NULL)
        yr_free(str);
      break;

    case OBJECT_TYPE_ARRAY:
      if (((YR_OBJECT_ARRAY*) object)->prototype_item != NULL)
        yr_object_destroy(((YR_OBJECT_ARRAY*) object)->prototype_item);

      array_items = ((YR_OBJECT_ARRAY*) object)->items;

      if (array_items != NULL)
      {
        for (i = 0; i < array_items->count; i++)
          if (array_items->objects[i] != NULL)
            yr_object_destroy(array_items->objects[i]);
      }

      yr_free(array_items);
      break;

    case OBJECT_TYPE_DICTIONARY:
      if (((YR_OBJECT_DICTIONARY*) object)->prototype_item != NULL)
        yr_object_destroy(((YR_OBJECT_DICTIONARY*) object)->prototype_item);

      dict_items = ((YR_OBJECT_DICTIONARY*) object)->items;

      if (dict_items != NULL)
      {
        for (i = 0; i < dict_items->used; i++)
        {
          if (dict_items->objects[i].key != NULL)
            yr_free(dict_items->objects[i].key);

          if (dict_items->objects[i].obj != NULL)
            yr_object_destroy(dict_items->objects[i].obj);
        }
      }

      yr_free(dict_items);
      break;

    case OBJECT_TYPE_FUNCTION:
      yr_object_destroy(((YR_OBJECT_FUNCTION*) object)->return_obj);
      break;
  }

  yr_free((void*) object->identifier);
  yr_free(object);
}
