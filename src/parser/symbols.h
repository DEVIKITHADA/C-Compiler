#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "parser.h"

// This is the symbol table used in the compiler.
// It holds variables (including functions), structs/unions, and typedefs.
// These three have different namespaces, but the same scoping rules.

// The pre-processor has its own symbol table, since it does not follow the same
// scoping rules.

void symbols_push_scope(void);
void symbols_pop_scope(void);
void symbols_init(void);

struct symbol_identifier {
	enum {
		IDENT_VARIABLE,
		IDENT_VARIABLE_LENGTH_ARRAY,
		IDENT_CONSTANT,
		IDENT_LABEL,
	} type;

	union {
		struct constant constant;
		struct {
			struct type *type;
			var_id id;
		} variable;
		struct {
			struct type *type;
			var_id id;
		} variable_length_array;
		struct {
			struct type *type;
			const char *name;
		} label;
	};

	int is_global;
	int is_tentative;
	int has_definition;
};

struct type *symbols_get_identifier_type(struct symbol_identifier *symbol);

struct symbol_identifier *symbols_add_identifier_global(const char *name);
struct symbol_identifier *symbols_get_identifier_global(const char *name);

struct symbol_identifier *symbols_add_identifier(const char *name);
struct symbol_identifier *symbols_get_identifier(const char *name);
struct symbol_identifier *symbols_get_identifier_in_current_scope(const char *name);

struct symbol_struct {
	enum {
		STRUCT_STRUCT,
		STRUCT_UNION,
		STRUCT_ENUM
	} type;

	struct struct_data *struct_data;
	struct enum_data *enum_data;
};

struct symbol_struct *symbols_add_struct(const char *name);
struct symbol_struct *symbols_get_struct(const char *name);
struct symbol_struct *symbols_get_struct_in_current_scope(const char *name);

struct symbol_typedef {
	struct type *data_type;
};

struct symbol_typedef *symbols_add_typedef(const char *name);
struct symbol_typedef *symbols_get_typedef(const char *name);

#endif
