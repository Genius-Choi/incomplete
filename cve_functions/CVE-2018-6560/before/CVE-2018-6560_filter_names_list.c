filter_names_list (FlatpakProxyClient *client, Buffer *buffer)
{
  GDBusMessage *message = g_dbus_message_new_from_blob (buffer->data, buffer->size, 0, NULL);
  GVariant *body, *arg0, *new_names;
  const gchar **names;
  int i;
  GVariantBuilder builder;
  Buffer *filtered;

  if (message == NULL ||
      (body = g_dbus_message_get_body (message)) == NULL ||
      (arg0 = g_variant_get_child_value (body, 0)) == NULL ||
      !g_variant_is_of_type (arg0, G_VARIANT_TYPE_STRING_ARRAY))
    return NULL;

  names = g_variant_get_strv (arg0, NULL);

  g_variant_builder_init (&builder, G_VARIANT_TYPE_STRING_ARRAY);
  for (i = 0; names[i] != NULL; i++)
    {
      if (flatpak_proxy_client_get_policy (client, names[i]) >= FLATPAK_POLICY_SEE)
        g_variant_builder_add (&builder, "s", names[i]);
    }
  g_free (names);

  new_names = g_variant_builder_end (&builder);
  g_dbus_message_set_body (message,
                           g_variant_new_tuple (&new_names, 1));

  filtered = message_to_buffer (message);
  g_object_unref (message);
  return filtered;
}
