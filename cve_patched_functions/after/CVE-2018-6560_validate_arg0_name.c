validate_arg0_name (FlatpakProxyClient *client, Buffer *buffer, FlatpakPolicy required_policy, FlatpakPolicy *has_policy)
{
  GDBusMessage *message = g_dbus_message_new_from_blob (buffer->data, buffer->size, 0, NULL);
  GVariant *body, *arg0;
  const char *name;
  FlatpakPolicy name_policy;
  gboolean res = FALSE;

  if (has_policy)
    *has_policy = FLATPAK_POLICY_NONE;

  if (message != NULL &&
      (body = g_dbus_message_get_body (message)) != NULL &&
      (arg0 = g_variant_get_child_value (body, 0)) != NULL &&
      g_variant_is_of_type (arg0, G_VARIANT_TYPE_STRING))
    {
      name = g_variant_get_string (arg0, NULL);
      name_policy = flatpak_proxy_client_get_policy (client, name);

      if (has_policy)
        *has_policy = name_policy;

      if (name_policy >= required_policy)
        res = TRUE;
      else if (client->proxy->log_messages)
        g_print ("Filtering message due to arg0 %s, policy: %d (required %d)\n", name, name_policy, required_policy);
    }

  g_object_unref (message);
  return res;
}
