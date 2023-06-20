#ifndef __COBJ_IMPLS_H__
#	define __COBJ_IMPLS_H__
#	define get(klass, instance, field, ...) \
			klass##_get_##field(instance, ## __VA_ARGS__)
#	define set(klass, instance, field, ...) \
			klass##_set_##field(instance, ## __VA_ARGS__)
#	define new(klass, ...) klass##_new(__VA_ARGS__)
#	define del(klass, ...) klass##_del(__VA_ARGS__)
#	define ask(klass, fun, ...) klass##_##fun(__VA_ARGS__)
#endif /* __COBJ_IMPLS_H__ */

#if defined(__USE_C_OBJSYS__)
#	undef GETTER
#	undef SETTER
#	undef DEFINE
#	undef NEW
#	undef DEL
#	undef __USE_C_OBJSYS__
#elif defined(__COBJ_PRIV_IMPLS_H__)
#	define UNUSED(arg) while(0 && (arg))
#	define GETTER(klass, field, type, body, ...) \
					type klass##_get_##field(klass self, ## __VA_ARGS__) \
					body
#	define SETTER(klass, field, type, body, ...) \
					bool klass##_set_##field(klass self, ## __VA_ARGS__, type value) \
					body
#	define DEFINE(klass, name, type, body, ...) \
					type klass##_##name(klass self, ## __VA_ARGS__) \
					body
#	define NEW(klass, body, ...) \
				klass klass ## _new(__VA_ARGS__) \
				body
#	define DEL(klass, body, ...) \
				void   klass ## _del(klass self, ## __VA_ARGS__) \
				body
#else
#	define GETTER(klass, field, type, ...) \
					type klass##_get_##field(klass self, ## __VA_ARGS__)
#	define SETTER(klass, field, type, ...) \
					bool klass##_set_##field(klass self, ## __VA_ARGS__, type value)
#	define DEFINE(klass, name, type, ...) \
					type klass##_##name(klass self, ## __VA_ARGS__)
#	define NEW(klass, ...) klass klass ## _new(__VA_ARGS__)
#	define DEL(klass, ...) void   klass ## _del(klass self, ## __VA_ARGS__)
#	define __USE_C_OBJSYS__
#endif
