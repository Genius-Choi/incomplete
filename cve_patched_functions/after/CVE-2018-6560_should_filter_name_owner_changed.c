should_filter_name_owner_changed (FlatpakProxyClient *client, Buffer *buffer)
{
  GDBusMessage *message = g_dbus_message_new_from_blob (buffer->data, buffer->size, 0, NULL);
  GVariant *body, *arg0, *arg1, *arg2;
  const gchar *name, *old, *new;
  gboolean filter = TRUE;

  if (message == NULL ||
      (body = g_dbus_message_get_body (message)) == NULL ||
      (arg0 = g_variant_get_child_value (body, 0)) == NULL ||
      !g_variant_is_of_type (arg0, G_VARIANT_TYPE_STRING) ||
      (arg1 = g_variant_get_child_value (body, 1)) == NULL ||
      !g_variant_is_of_type (arg1, G_VARIANT_TYPE_STRING) ||
      (arg2 = g_variant_get_child_value (body, 2)) == NULL ||
      !g_variant_is_of_type (arg2, G_VARIANT_TYPE_STRING))
    return TRUE;

  name = g_variant_get_string (arg0, NULL);
  old = g_variant_get_string (arg1, NULL);
  new = g_variant_get_string (arg2, NULL);

  if (flatpak_proxy_client_get_policy (client, name) >= FLATPAK_POLICY_SEE ||
      (client->proxy->sloppy_names && name[0] == ':'))
    {
      if (name[0] != ':')
        {
          if (old[0] != 0)
            flatpak_proxy_client_update_unique_id_policy_from_name (client, old, name);

          if (new[0] != 0)
            flatpak_proxy_client_update_unique_id_policy_from_name (client, new, name);
        }

      filter = FALSE;
    }

  g_object_unref (message);

  return filter;
}
