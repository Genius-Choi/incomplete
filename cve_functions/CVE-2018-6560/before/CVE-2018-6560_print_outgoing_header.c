print_outgoing_header (Header *header)
{
  switch (header->type)
    {
    case G_DBUS_MESSAGE_TYPE_METHOD_CALL:
      g_print ("C%d: -> %s call %s.%s at %s\n",
               header->serial,
               header->destination ? header->destination : "(no dest)",
               header->interface ? header->interface : "",
               header->member ? header->member : "",
               header->path ? header->path : "");
      break;

    case G_DBUS_MESSAGE_TYPE_METHOD_RETURN:
      g_print ("C%d: -> %s return from B%d\n",
               header->serial,
               header->destination ? header->destination : "(no dest)",
               header->reply_serial);
      break;

    case G_DBUS_MESSAGE_TYPE_ERROR:
      g_print ("C%d: -> %s return error %s from B%d\n",
               header->serial,
               header->destination ? header->destination : "(no dest)",
               header->error_name ? header->error_name : "(no error)",
               header->reply_serial);
      break;

    case G_DBUS_MESSAGE_TYPE_SIGNAL:
      g_print ("C%d: -> %s signal %s.%s at %s\n",
               header->serial,
               header->destination ? header->destination : "all",
               header->interface ? header->interface : "",
               header->member ? header->member : "",
               header->path ? header->path : "");
      break;

    default:
      g_print ("unknown message type\n");
    }
}
