CURLcode Curl_auth_create_external_message(struct Curl_easy *data,
                                           const char *user, char **outptr,
                                           size_t *outlen)
{
  /* This is the same formatting as the login message */
  return Curl_auth_create_login_message(data, user, outptr, outlen);
}
