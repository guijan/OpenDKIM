/*
**  Copyright (c) 2005-2008 Sendmail, Inc. and its suppliers.
**    All rights reserved.
**
**  Copyright (c) 2009, The OpenDKIM Project.  All rights reserved.
*/

#ifndef lint
static char t_test69_c_id[] = "@(#)$Id: t-test69.c,v 1.2 2009/07/20 21:41:08 cm-msk Exp $";
#endif /* !lint */

/* system includes */
#include <sys/types.h>
#include <assert.h>
#include <string.h>
#include <stdio.h>


/* libdkim includes */
#include "dkim.h"
#include "t-testdata.h"

#define	MAXHEADER	4096

#define SIG2 "v=1; a=rsa-sha1; c=relaxed/simple; d=example.com; s=test;\r\n\tt=1172620939; bh=ll/0h2aWgG+D3ewmE4Y3pY7Ukz8=; h=Received:Received:\r\n\t Received:From:To:Date:Subject:Message-ID; b=bj9kVUbnBYfe9sVzH9lT45\r\n\tTFKO3eQnDbXLfgmgu/b5QgxcnhT9ojnV2IAM4KUO8+hOo5sDEu5Co/0GASH0vHpSV4P\r\n\t377Iwew3FxvLpHsVbVKgXzoKD4QSbHRpWNxyL6LypaaqFa96YqjXuYXr0vpb88hticn\r\n\t6I16//WThMz8fMU="

/*
**  MAIN -- program mainline
**
**  Parameters:
**  	The usual.
**
**  Return value:
**  	Exit status.
*/

int
main(int argc, char **argv)
{
	u_int flags;
	DKIM_STAT status;
	DKIM *dkim;
	DKIM_LIB *lib;
	dkim_query_t qtype = DKIM_QUERY_FILE;
	unsigned char hdr[MAXHEADER + 1];

	printf("*** relaxed/simple rsa-sha1 verifying with delayed processing\n");

	/* instantiate the library */
	lib = dkim_init(NULL, NULL);
	assert(lib != NULL);

	/* set flags */
	flags = DKIM_LIBFLAGS_DELAYSIGPROC;
#ifdef TEST_KEEP_FILES
	flags |= (DKIM_LIBFLAGS_TMPFILES|DKIM_LIBFLAGS_KEEPFILES);
#endif /* TEST_KEEP_FILES */
	(void) dkim_options(lib, DKIM_OP_SETOPT, DKIM_OPTS_FLAGS, &flags,
	                    sizeof flags);

	(void) dkim_options(lib, DKIM_OP_SETOPT, DKIM_OPTS_QUERYMETHOD,
	                    &qtype, sizeof qtype);
	(void) dkim_options(lib, DKIM_OP_SETOPT, DKIM_OPTS_QUERYINFO,
	                    KEYFILE, strlen(KEYFILE));

	dkim = dkim_verify(lib, JOBID, NULL, &status);
	assert(dkim != NULL);

	snprintf(hdr, sizeof hdr, "%s: %s", DKIM_SIGNHEADER, SIG2);
	status = dkim_header(dkim, hdr, strlen(hdr));
	assert(status == DKIM_STAT_OK);

	status = dkim_header(dkim, HEADER01, strlen(HEADER01));
	assert(status == DKIM_STAT_OK);

	status = dkim_header(dkim, HEADER02, strlen(HEADER02));
	assert(status == DKIM_STAT_OK);

	status = dkim_header(dkim, HEADER03, strlen(HEADER03));
	assert(status == DKIM_STAT_OK);

	status = dkim_header(dkim, HEADER04, strlen(HEADER04));
	assert(status == DKIM_STAT_OK);

	status = dkim_header(dkim, HEADER05, strlen(HEADER05));
	assert(status == DKIM_STAT_OK);

	status = dkim_header(dkim, HEADER06, strlen(HEADER06));
	assert(status == DKIM_STAT_OK);

	status = dkim_header(dkim, HEADER07, strlen(HEADER07));
	assert(status == DKIM_STAT_OK);

	status = dkim_header(dkim, HEADER08, strlen(HEADER08));
	assert(status == DKIM_STAT_OK);

	status = dkim_header(dkim, HEADER09, strlen(HEADER09));
	assert(status == DKIM_STAT_OK);

	status = dkim_eoh(dkim);
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY00, strlen(BODY00));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY01, strlen(BODY01));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY01A, strlen(BODY01A));
	assert(status == DKIM_STAT_OK);
	status = dkim_body(dkim, BODY01B, strlen(BODY01B));
	assert(status == DKIM_STAT_OK);
	status = dkim_body(dkim, BODY01C, strlen(BODY01C));
	assert(status == DKIM_STAT_OK);
	status = dkim_body(dkim, BODY01D, strlen(BODY01D));
	assert(status == DKIM_STAT_OK);
	status = dkim_body(dkim, BODY01E, strlen(BODY01E));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY02, strlen(BODY02));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY03, strlen(BODY03));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY04, strlen(BODY04));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY03, strlen(BODY03));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY03, strlen(BODY03));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY05, strlen(BODY05));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY03, strlen(BODY03));
	assert(status == DKIM_STAT_OK);

	status = dkim_body(dkim, BODY03, strlen(BODY03));
	assert(status == DKIM_STAT_OK);

	status = dkim_eom(dkim, NULL);
	assert(status == DKIM_STAT_OK);

	status = dkim_free(dkim);
	assert(status == DKIM_STAT_OK);

	dkim_close(lib);

	return 0;
}
