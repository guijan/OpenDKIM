/*
**  Copyright (c) 2009, The OpenDKIM Project.  All rights reserved.
*/

#ifndef _MANUAL_H_
#define _MANUAL_H_

#ifndef lint
static char manual_h_id[] = "@(#)$Id: manual.h,v 1.4 2009/12/10 22:17:30 cm-msk Exp $";
#endif /* !lint */

/* system includes */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>

/* PROTOTYPES */
#ifdef AF_INET6
extern int ar_res_parse(int *, struct sockaddr_storage *, int *, long *);
#else /* AF_INET6 */
extern int ar_res_parse(int *, struct sockaddr_in *, int *, long *);
#endif /* AF_INET6 */

#endif /* ! _MANUAL_H_ */