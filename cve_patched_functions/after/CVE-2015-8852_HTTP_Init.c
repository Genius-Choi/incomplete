HTTP_Init(void)
{

#define HTTPH(a, b, c, d, e, f, g) b[0] = (char)strlen(b + 1);
#include "http_headers.h"
#undef HTTPH
}
