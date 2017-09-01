/*
 *  database_commands.h
 *  lh
 *
 *  Created by Anders Bolt-Evensen on 19.06.10.
 *  Copyright 2010 Høgskolen i Østfold. All rights reserved.
 *
 */

void createDatabase(char *u);
void createTable();
void insertTable();
void insertBooks();
void insertEpisodes();
void insertSeasons();
void insertCharacters();
void insertTowns();
void catch_int7(int sig_num);
void catch_int6(int sig_num);
void catch_int5(int sig_num);
void catch_int4(int sig_num);
void catch_int3(int sig_num);
void catch_int2(int sig_num);
void catch_int(int sig_num);
void usernameAndPasswordInitialize();
int search();
void exitApp(int errCode, char *errMsg);
