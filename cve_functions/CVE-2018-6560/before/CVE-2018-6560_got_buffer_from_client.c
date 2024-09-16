got_buffer_from_client (FlatpakProxyClient *client, ProxySide *side, Buffer *buffer)
{
  ExpectedReplyType expecting_reply = EXPECTED_REPLY_NONE;

  if (client->authenticated && client->proxy->filter)
    {
      g_autoptr(Header) header = NULL;;
      BusHandler handler;

      /* Filter and rewrite outgoing messages as needed */

      header = parse_header (buffer, client->serial_offset, 0, 0);
      if (header == NULL)
        {
          g_warning ("Invalid message header format");
          side_closed (side);
          buffer_unref (buffer);
          return;
        }

      if (!update_socket_messages (side, buffer, header))
        return;

      /* Make sure the client is not playing games with the serials, as that
         could confuse us. */
      if (header->serial <= client->last_serial)
        {
          g_warning ("Invalid client serial");
          side_closed (side);
          buffer_unref (buffer);
          return;
        }
      client->last_serial = header->serial;

      if (client->proxy->log_messages)
        print_outgoing_header (header);

      /* Keep track of the initial Hello request so that we can read
         the reply which has our assigned unique id */
      if (is_dbus_method_call (header) &&
          g_strcmp0 (header->member, "Hello") == 0)
        {
          expecting_reply = EXPECTED_REPLY_HELLO;
          client->hello_serial = header->serial;
        }

      handler = get_dbus_method_handler (client, header);

      switch (handler)
        {
        case HANDLE_FILTER_HAS_OWNER_REPLY:
        case HANDLE_FILTER_GET_OWNER_REPLY:
          if (!validate_arg0_name (client, buffer, FLATPAK_POLICY_SEE, NULL))
            {
              g_clear_pointer (&buffer, buffer_unref);
              if (handler == HANDLE_FILTER_GET_OWNER_REPLY)
                buffer = get_error_for_roundtrip (client, header,
                                                  "org.freedesktop.DBus.Error.NameHasNoOwner");
              else
                buffer = get_bool_reply_for_roundtrip (client, header, FALSE);

              expecting_reply = EXPECTED_REPLY_REWRITE;
              break;
            }

          goto handle_pass;

        case HANDLE_VALIDATE_MATCH:
          if (!validate_arg0_match (client, buffer))
            {
              if (client->proxy->log_messages)
                g_print ("*DENIED* (ping)\n");
              g_clear_pointer (&buffer, buffer_unref);
              buffer = get_error_for_roundtrip (client, header,
                                                "org.freedesktop.DBus.Error.AccessDenied");
              expecting_reply = EXPECTED_REPLY_REWRITE;
              break;
            }

          goto handle_pass;

        case HANDLE_VALIDATE_OWN:
        case HANDLE_VALIDATE_SEE:
        case HANDLE_VALIDATE_TALK:
          {
            FlatpakPolicy name_policy;
            if (validate_arg0_name (client, buffer, policy_from_handler (handler), &name_policy))
              goto handle_pass;

            if (name_policy < (int) FLATPAK_POLICY_SEE)
              goto handle_hide;
            else
              goto handle_deny;
          }

        case HANDLE_FILTER_NAME_LIST_REPLY:
          expecting_reply = EXPECTED_REPLY_LIST_NAMES;
          goto handle_pass;

        case HANDLE_PASS:
handle_pass:
          if (client_message_generates_reply (header))
            {
              if (expecting_reply == EXPECTED_REPLY_NONE)
                expecting_reply = EXPECTED_REPLY_NORMAL;
            }

          break;

        case HANDLE_HIDE:
handle_hide:
          g_clear_pointer (&buffer, buffer_unref);

          if (client_message_generates_reply (header))
            {
              const char *error;

              if (client->proxy->log_messages)
                g_print ("*HIDDEN* (ping)\n");

              if ((header->destination != NULL && header->destination[0] == ':') ||
                  (header->flags & G_DBUS_MESSAGE_FLAGS_NO_AUTO_START) != 0)
                error = "org.freedesktop.DBus.Error.NameHasNoOwner";
              else
                error = "org.freedesktop.DBus.Error.ServiceUnknown";

              buffer = get_error_for_roundtrip (client, header, error);
              expecting_reply = EXPECTED_REPLY_REWRITE;
            }
          else
            {
              if (client->proxy->log_messages)
                g_print ("*HIDDEN*\n");
            }
          break;

        default:
        case HANDLE_DENY:
handle_deny:
          g_clear_pointer (&buffer, buffer_unref);

          if (client_message_generates_reply (header))
            {
              if (client->proxy->log_messages)
                g_print ("*DENIED* (ping)\n");

              buffer = get_error_for_roundtrip (client, header,
                                                "org.freedesktop.DBus.Error.AccessDenied");
              expecting_reply = EXPECTED_REPLY_REWRITE;
            }
          else
            {
              if (client->proxy->log_messages)
                g_print ("*DENIED*\n");
            }
          break;
        }

      if (buffer != NULL && expecting_reply != EXPECTED_REPLY_NONE)
        queue_expected_reply (side, header->serial, expecting_reply);
    }

  if (buffer)
    queue_outgoing_buffer (&client->bus_side, buffer);

  if (buffer != NULL && expecting_reply == EXPECTED_REPLY_HELLO)
    queue_initial_name_ops (client);
}
