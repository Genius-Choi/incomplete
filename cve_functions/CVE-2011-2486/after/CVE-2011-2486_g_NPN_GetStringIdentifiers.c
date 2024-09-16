g_NPN_GetStringIdentifiers(const NPUTF8 **names, int32_t nameCount, NPIdentifier *identifiers)
{
  if (!thread_check()) {
	npw_printf("WARNING: NPN_GetStringIdentifiers not called from the main thread\n");
	return;
  }

  if (names == NULL)
	return;

  if (identifiers == NULL)
	return;

  D(bugiI("NPN_GetStringIdentifiers names=%p\n", names));
  cached_NPN_GetStringIdentifiers(names, nameCount, identifiers);
  D(bugiD("NPN_GetStringIdentifiers done\n"));
}
