const=a
CC=gcc
SQL_OBJ=sqlite3.o
LIBNAME=libsqlite3
NAME= ../lib/$(LIBNAME).$(const)
R_CFLAGS = -std=c89 -DSQLITE_ENABLE_UPDATE_DELETE_LIMIT=1


all : $(NAME)

$(NAME) : $(SQL_OBJ)
	@cp sqlite3.h ../inc
	@$(AR) rcs $@ $< 
	

$(SQL_OBJ): sqlite3.c sqlite3.h
	@$(CC) -c $(R_CFLAGS) $< 

uninstall: clean
	@rm -rf $(NAME)

clean:
	@rm -rf $(SQL_OBJ)
	@rm -rf ../inc/sqlite3.h

reinstall: uninstall all