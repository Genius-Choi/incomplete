streamExtNegList(SOPClassExtendedNegotiationSubItemList *lst, unsigned char *b, unsigned long *length)
{
  OFCondition cond = EC_Normal;
  unsigned long localLength;

  *length = 0;

  if (lst == NULL)
    return EC_Normal;

  OFListIterator(SOPClassExtendedNegotiationSubItem*) i = lst->begin();
  while (i != lst->end()) {
    localLength = 0;
    cond = streamExtNeg(*i, b, &localLength);
    if (cond.bad())
      return cond;
    *length += localLength;
    b += localLength;
    ++i;
  }
  return EC_Normal;
}
