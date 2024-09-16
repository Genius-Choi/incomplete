uripRead(void * context, char * buffer, int len) {
   const char *ptr = (const char *) context;

   if ((context == NULL) || (buffer == NULL) || (len < 0))
       return(-1);

   if (len > urip_rlen) len = urip_rlen;
   memcpy(buffer, ptr, len);
   urip_rlen -= len;
   return(len);
}
