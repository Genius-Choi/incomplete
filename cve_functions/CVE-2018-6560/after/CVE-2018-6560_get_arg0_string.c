get_arg0_string (Buffer *buffer)
{
  GDBusMessage *message = g_dbus_message_new_from_blob (buffer->data, buffer->size, 0, NULL);
  GVariant *body;
  g_autoptr(GVariant) arg0 = NULL;
  char *name = NULL;

  if (message != NULL &&
      (body = g_dbus_message_get_body (message)) != NULL &&
      (arg0 = g_variant_get_child_value (body, 0)) != NULL &&
      g_variant_is_of_type (arg0, G_VARIANT_TYPE_STRING))
    name = g_variant_dup_string (arg0, NULL);

  g_object_unref (message);

  return name;
}
