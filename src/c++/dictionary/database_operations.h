/*
 *  database_operations.h
 *  dictionary
 *
 *  Created by Anders Bolt-Evensen on 4/5/10.
 *  Copyright 2010 Høgskolen i Østfold. All rights reserved.
 *
 */
#include <mysql.h>
int createDatabase(char *user, char *password, char *database);
int createTable(char *user, char *password, char *database);