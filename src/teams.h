#ifndef __TEAMS_H__
#	define __TEAMS_H__
#	define __TEAMS_PRIVATE_H__
#	include <stdint.h>
#	include <stdbool.h>
#	include "teams-hell.h"
// Type definition
typedef struct team_impl_struct * TEAM;

// base functions
NEW(team, TEAM);
DEL(team, TEAM);

// field getters
SETTER(team, name,			TEAM, char *);
SETTER(team, institution,	TEAM, char *);
SETTER(team, member_name,	TEAM, char *, int);
SETTER(team, solved,		TEAM, uint8_t);

// field setters
GETTER(team, name,			TEAM, char *);
GETTER(team, institution,	TEAM, char *);
GETTER(team, member_name,	TEAM, char *, int);
GETTER(team, solved,		TEAM, uint8_t);

// helper functions
DEFINE(team, printf,  		TEAM,  int);
DEFINE(team, fprintf, 		TEAM,  int, FILE *);
DEFINE(team, find_champion, TEAM, TEAM, TEAM *, unsigned num);

#	define __TEAMS_PRIVATE_UNDEF__
#	include "teams-hell.h"
#endif /* __TEAMS_H__ */
