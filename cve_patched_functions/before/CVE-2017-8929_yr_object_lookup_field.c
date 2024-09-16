YR_OBJECT* yr_object_lookup_field(
    YR_OBJECT* object,
    const char* field_name)
{
  YR_STRUCTURE_MEMBER* member;

  assert(object != NULL);
  assert(object->type == OBJECT_TYPE_STRUCTURE);

  member = ((YR_OBJECT_STRUCTURE*) object)->members;

  while (member != NULL)
  {
    if (strcmp(member->object->identifier, field_name) == 0)
      return member->object;

    member = member->next;
  }

  return NULL;
}
