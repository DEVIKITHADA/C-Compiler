#ifndef CODEGEN_H
#define CODEGEN_H

extern struct codegen_flags {
	enum {
		CMODEL_SMALL,
		CMODEL_LARGE
	} cmodel;
} codegen_flags;

struct variable_info {
	enum {
		VAR_STOR_NONE,
		VAR_STOR_STACK
	} storage;

	int stack_location;
};

extern struct variable_info *variable_info;

void set_section(const char *section);
void emit(const char *fmt, ...);
void emit_no_newline(const char *fmt, ...);
void emit_char(char c); // Used for string printing.

void codegen(const char *path);

#endif
