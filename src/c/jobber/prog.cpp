#include <iostream>
#include <string>
#include <postgresql92/libpq-fe.h>
#include <postgresql92/libpq/libpq-fs.h>

using namespace std;

int main()
{
  execute_query();
}

using namespace pqxx;  
  
void execute_query() {  
    connection cn("dbname=jobber");  
    work w(cn, "mytransaction");  
    w.exec("INSERT INTO tbl_postnr_std(postnummber, poststed) VALUES (1650, 'Et sted');");  
    w.commit();  
} 
