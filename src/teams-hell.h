#if defined(__TEAMS_H__) || defined(__TEAMS_PRIVATE_UNDEF__)

#	ifndef __TEAMS_HELL_H__
#		define __TEAMS_HELL_H__
#		define get(klass, instance, field, ...) \
				klass##_get_##field(instance, ## __VA_ARGS__)
#		define set(klass, instance, field, ...) \
				klass##_set_##field(instance, ## __VA_ARGS__)
#		define new(klass, ...) klass##_new(__VA_ARGS__)
#		define del(klass, ...) klass##_del(__VA_ARGS__)
#		define fun(klass, fun, ...) klass##_##fun(__VA_ARGS__)
#	endif /* __TEAMS_HELL_H__ */

#	if defined(__TEAMS_PRIVATE_UNDEF__)
#		undef GETTER
#		undef SETTER
#		undef DEFINE
#		undef NEW
#		undef DEL
#		undef __TEAMS_PRIVATE_UNDEF__
#		undef __TEAMS_PRIVATE_H__
#	elif defined(__IMPL_TEAMS_INTERNAL)
#		define UNUSED(arg) while(0 && (arg))
#		define GETTER(klass, field, struct, type, body, ...) \
						type klass##_get_##field(struct self, ## __VA_ARGS__) \
						body
#		define SETTER(klass, field, struct, type, body, ...) \
						bool klass##_set_##field(struct self, ## __VA_ARGS__, type value) \
						body
#		define DEFINE(klass, name, struct, type, body, ...) \
						type klass##_##name(struct self, ## __VA_ARGS__) \
						body
#		define NEW(klass, struct, body, ...) \
					struct klass ## _new(__VA_ARGS__) \
					body
#		define DEL(klass, struct, body, ...) \
					void   klass ## _del(struct self, ## __VA_ARGS__) \
					body
#	elif defined(__TEAMS_PRIVATE_H__)
#		define GETTER(klass, field, struct, type, ...) \
				type klass##_get_##field(struct self, ## __VA_ARGS__)
#		define SETTER(klass, field, struct, type, ...) \
				bool klass##_set_##field(struct self, ## __VA_ARGS__, type value)
#		define DEFINE(klass, name, struct, type, ...) \
				type klass##_##name(struct self, ## __VA_ARGS__)
#		define NEW(klass, struct, ...) struct klass ## _new(__VA_ARGS__)
#		define DEL(klass, struct, ...) void   klass ## _del(struct self, ## __VA_ARGS__)
#	endif

#endif
