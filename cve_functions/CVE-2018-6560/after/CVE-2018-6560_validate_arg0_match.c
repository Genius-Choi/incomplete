validate_arg0_match (FlatpakProxyClient *client, Buffer *buffer)
{
  GDBusMessage *message = g_dbus_message_new_from_blob (buffer->data, buffer->size, 0, NULL);
  GVariant *body, *arg0;
  const char *match;
  gboolean res = TRUE;

  if (message != NULL &&
      (body = g_dbus_message_get_body (message)) != NULL &&
      (arg0 = g_variant_get_child_value (body, 0)) != NULL &&
      g_variant_is_of_type (arg0, G_VARIANT_TYPE_STRING))
    {
      match = g_variant_get_string (arg0, NULL);
      if (strstr (match, "eavesdrop=") != NULL)
        res = FALSE;
    }

  g_object_unref (message);
  return res;
}
