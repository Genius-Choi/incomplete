bool Curl_nss_cert_status_request(void)
{
#ifdef SSL_ENABLE_OCSP_STAPLING
  return TRUE;
#else
  return FALSE;
#endif
}
