#ifndef __TEAMS_H__
#	define __TEAMS_H__
#	include <stdint.h>
#	include <stdbool.h>
#	define GETTER(klass, field, struct, type, ...) \
				type klass##_get_##field(struct self, ## __VA_ARGS__)
#	define SETTER(klass, field, struct, type, ...) \
				bool klass##_set_##field(struct self, ## __VA_ARGS__, type value)
#	define DEFINE(klass, name, struct, type, ...) \
				type klass##_##name(struct self, ## __VA_ARGS__)
#	define UNUSED(arg) while(0 && (arg))
#	define get(klass, instance, field, ...) \
				klass##_get_##field(instance, ## __VA_ARGS__)
#	define set(klass, instance, field, ...) \
				klass##_set_##field(instance, ## __VA_ARGS__)
#	define new(klass, ...) klass##_new(__VA_ARGS__)
#	define fun(klass, fun, ...) klass##_##fun(__VA_ARGS__)
// Type definition
typedef struct team_impl_struct * TEAM;

// base functions
TEAM team_new();
void team_del(TEAM team);

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

#	ifndef __IMPL_TEAMS_INTERNAL
#		undef GETTER
#		undef SETTER
#		undef DEFINE
#		undef UNUSED
#	endif
#endif /* __TEAMS_H__ */
