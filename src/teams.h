#ifndef __TEAMS_H__
#	define __TEAMS_H__
#	include <stdint.h>
#	include <stdbool.h>
#	include "cobj.h"
// Type definition
typedef struct team_impl_struct * team;

// base functions
NEW(team);
DEL(team);

// field getters
SETTER(team, name,			char *);
SETTER(team, institution,	char *);
SETTER(team, member_name,	char *, int);
SETTER(team, solved,		uint8_t);

// field setters
GETTER(team, name,			char *);
GETTER(team, institution,	char *);
GETTER(team, member_name,	char *, int);
GETTER(team, solved,		uint8_t);

// helper functions
DEFINE(team, printf,  		int);
DEFINE(team, fprintf, 		int, FILE *);
DEFINE(team, find_champion, team, team *, unsigned);

#	include "cobj.h"
#endif /* __TEAMS_H__ */
