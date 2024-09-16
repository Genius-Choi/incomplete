http_FilterFields(struct worker *w, int fd, struct http *to,
    const struct http *fm, unsigned how)
{
	unsigned u;

	CHECK_OBJ_NOTNULL(fm, HTTP_MAGIC);
	CHECK_OBJ_NOTNULL(to, HTTP_MAGIC);
	to->nhd = HTTP_HDR_FIRST;
	to->status = fm->status;
	for (u = HTTP_HDR_FIRST; u < fm->nhd; u++) {
		if (fm->hd[u].b == NULL)
			continue;
		if (fm->hdf[u] & HDF_FILTER)
			continue;
#define HTTPH(a, b, c, d, e, f, g) \
		if (((e) & how) && http_IsHdr(&fm->hd[u], (b))) \
			continue;
#include "http_headers.h"
#undef HTTPH
		http_copyheader(w, fd, to, fm, u);
	}
}
