policy_from_handler (BusHandler handler)
{
  switch (handler)
    {
    case HANDLE_VALIDATE_OWN:
      return FLATPAK_POLICY_OWN;

    case HANDLE_VALIDATE_TALK:
      return FLATPAK_POLICY_TALK;

    case HANDLE_VALIDATE_SEE:
      return FLATPAK_POLICY_SEE;

    default:
      return FLATPAK_POLICY_NONE;
    }
}
