parse_opt (int key, char *arg, struct argp_state *state)
{
  switch (key)
    {
    case OPTION_CONSOLE_SOCKET:
      exec_options.console_socket = arg;
      break;

    case OPTION_PID_FILE:
      exec_options.pid_file = arg;
      break;

    case OPTION_NO_NEW_PRIVS:
      exec_options.no_new_privs = true;
      break;

    case OPTION_PROCESS_LABEL:
      exec_options.process_label = argp_mandatory_argument (arg, state);
      break;

    case OPTION_APPARMOR:
      exec_options.apparmor = argp_mandatory_argument (arg, state);
      break;

    case OPTION_PRESERVE_FDS:
      exec_options.preserve_fds = strtoul (argp_mandatory_argument (arg, state), NULL, 10);
      break;

    case OPTION_CGROUP:
      exec_options.cgroup = argp_mandatory_argument (arg, state);
      break;

    case 'd':
      exec_options.detach = true;
      break;

    case 'p':
      exec_options.process = arg;
      break;

    case 't':
      exec_options.tty = arg == NULL || (strcmp (arg, "false") != 0 && strcmp (arg, "no") != 0);
      break;

    case 'u':
      exec_options.user = arg;
      break;

    case 'e':
      append_env (arg);
      break;

    case 'c':
      append_cap (arg);
      break;

    case OPTION_CWD:
      exec_options.cwd = xstrdup (arg);
      break;

    case ARGP_KEY_NO_ARGS:
      libcrun_fail_with_error (0, "please specify a ID for the container");

    default:
      return ARGP_ERR_UNKNOWN;
    }

  return 0;
}
