get_dbus_method_handler (FlatpakProxyClient *client, Header *header)
{
  FlatpakPolicy policy;
  const char *method;

  if (header->has_reply_serial)
    {
      ExpectedReplyType expected_reply =
        steal_expected_reply (&client->bus_side,
                              header->reply_serial);
      if (expected_reply == EXPECTED_REPLY_NONE)
        return HANDLE_DENY;

      return HANDLE_PASS;
    }

  policy = flatpak_proxy_client_get_policy (client, header->destination);
  if (policy < FLATPAK_POLICY_SEE)
    return HANDLE_HIDE;
  if (policy < FLATPAK_POLICY_FILTERED)
    return HANDLE_DENY;

  if (policy == FLATPAK_POLICY_FILTERED)
    {
      GList *filters = NULL, *l;

      if (header->destination)
        filters = g_hash_table_lookup (client->proxy->filters, header->destination);
      for (l = filters; l != NULL; l = l->next)
        {
          Filter *filter = l->data;

          if (header->type == G_DBUS_MESSAGE_TYPE_METHOD_CALL &&
              (filter->path == NULL || g_strcmp0 (filter->path, header->path) == 0) &&
              (filter->interface == NULL || g_strcmp0 (filter->interface, header->interface) == 0) &&
              (filter->member == NULL || g_strcmp0 (filter->member, header->member) == 0))
            return HANDLE_PASS;
        }

      return HANDLE_DENY;
    }

  if (!is_for_bus (header))
    return HANDLE_PASS;

  if (is_introspection_call (header))
    {
      return HANDLE_PASS;
    }
  else if (is_dbus_method_call (header))
    {
      method = header->member;
      if (method == NULL)
        return HANDLE_DENY;

      if (strcmp (method, "AddMatch") == 0)
        return HANDLE_VALIDATE_MATCH;

      if (strcmp (method, "Hello") == 0 ||
          strcmp (method, "RemoveMatch") == 0 ||
          strcmp (method, "GetId") == 0)
        return HANDLE_PASS;

      if (strcmp (method, "UpdateActivationEnvironment") == 0 ||
          strcmp (method, "BecomeMonitor") == 0)
        return HANDLE_DENY;

      if (strcmp (method, "RequestName") == 0 ||
          strcmp (method, "ReleaseName") == 0 ||
          strcmp (method, "ListQueuedOwners") == 0)
        return HANDLE_VALIDATE_OWN;

      if (strcmp (method, "NameHasOwner") == 0)
        return HANDLE_FILTER_HAS_OWNER_REPLY;

      if (strcmp (method, "GetNameOwner") == 0)
        return HANDLE_FILTER_GET_OWNER_REPLY;

      if (strcmp (method, "GetConnectionUnixProcessID") == 0 ||
          strcmp (method, "GetConnectionCredentials") == 0 ||
          strcmp (method, "GetAdtAuditSessionData") == 0 ||
          strcmp (method, "GetConnectionSELinuxSecurityContext") == 0 ||
          strcmp (method, "GetConnectionUnixUser") == 0)
        return HANDLE_VALIDATE_SEE;

      if (strcmp (method, "StartServiceByName") == 0)
        return HANDLE_VALIDATE_TALK;

      if (strcmp (method, "ListNames") == 0 ||
          strcmp (method, "ListActivatableNames") == 0)
        return HANDLE_FILTER_NAME_LIST_REPLY;

      g_warning ("Unknown bus method %s", method);
      return HANDLE_DENY;
    }
  else
    {
      return HANDLE_DENY;
    }
}
