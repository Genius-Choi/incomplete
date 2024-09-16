static CURLcode imap_logout(struct connectdata *conn)
{
  CURLcode result = CURLE_OK;
  const char *str;

  str = getcmdid(conn);

  result = imapsendf(conn, str, "%s LOGOUT", str, NULL);
  if(result)
    return result;
  state(conn, IMAP_LOGOUT);

  result = imap_easy_statemach(conn);

  return result;
}
