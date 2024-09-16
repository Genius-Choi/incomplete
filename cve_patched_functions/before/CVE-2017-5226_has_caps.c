has_caps (void)
{
  struct __user_cap_header_struct hdr = { _LINUX_CAPABILITY_VERSION_3, 0 };
  struct __user_cap_data_struct data[2] = { { 0 } };

  if (capget (&hdr, data)  < 0)
    die_with_error ("capget failed");

  return data[0].permitted != 0 || data[1].permitted != 0;
}
