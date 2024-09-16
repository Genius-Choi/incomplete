raptor_rss_parse_recognise_syntax(raptor_parser_factory* factory, 
                                  const unsigned char *buffer, size_t len,
                                  const unsigned char *identifier, 
                                  const unsigned char *suffix, 
                                  const char *mime_type)
{
  int score =  0;
  
  if(suffix) {
    if(!strcmp((const char*)suffix, "rss"))
      score = 7;
    if(!strcmp((const char*)suffix, "atom"))
      score = 5;
    if(!strcmp((const char*)suffix, "xml"))
      score = 4;
  }
  
  if(identifier) {
    if(!strncmp((const char*)identifier, "http://feed", 11))
      score += 5;
    else if(strstr((const char*)identifier, "feed"))
      score += 3;

    if(strstr((const char*)identifier, "rss2"))
      score += 5;
    else if(!suffix && strstr((const char*)identifier, "rss"))
      score += 4;
    else if(!suffix && strstr((const char*)identifier, "atom"))
      score += 4;
    else if(strstr((const char*)identifier, "rss.xml"))
      score += 4;
    else if(strstr((const char*)identifier, "atom.xml"))
      score += 4;
  }
  
  if(mime_type) {
    if(!strstr((const char*)mime_type, "html")) {
      if(strstr((const char*)mime_type, "rss"))
        score += 4;
      else if(strstr((const char*)mime_type, "xml"))
        score += 4;
      else if(strstr((const char*)mime_type, "atom"))
        score += 4;
    }
  }
  
  return score;
}
