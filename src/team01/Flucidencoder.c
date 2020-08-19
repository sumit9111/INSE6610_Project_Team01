

/// This dll extension is for DB Browser for SQLite to generate FLucid from tables
///// https://sqlitebrowser.org/

#include <stdio.h>
#include <assert.h>
#include "sqlite3ext.h"
#define MAX_SYNTAX_SIZE 1024


#pragma warning(disable : 4996)


SQLITE_EXTENSION_INIT1;

#include <stdlib.h>
 
void freeResult(void* ptr)
{
	if (ptr != NULL)
		free(ptr);
	return;
}

  
char* strAppendPointer(char* original, char* add)
{
	char* str3 = (char*)malloc(1 + strlen(original) + strlen(add));
	strcpy(str3, original);
	strcat(str3, add);
	return str3;

}


static void Flucidencoder(sqlite3_context* context, int argc, sqlite3_value** argv) {
	 
	assert(argc == 1);

	sqlite3* db = sqlite3_context_db_handle(context);

	const char* sql = "Select * from ";
	const char* tablename = sqlite3_value_text(argv[0]);
	char observation_buffer[10*MAX_SYNTAX_SIZE] = "observation sequence ";
	 
	strcat(observation_buffer, tablename);
	strcat(observation_buffer, " { ");
	 
	char* query = strAppendPointer(sql, tablename);
	
	 sqlite3_stmt* stmt;
	   
	 if (sqlite3_prepare_v2(db, query, strnlen(query), &stmt, NULL) == SQLITE_OK)
	 {

		int colcount= sqlite3_column_count(stmt);
		char temp[250];
		int idx = 1;
		char observation_buffer2[500];
		char* observation_buffer3 = "";

		while (sqlite3_step(stmt) == SQLITE_ROW)
		{
			 
			 sprintf(temp, "%s%d%s", "\r\nItem_O_", idx, ",");
			 strcat(observation_buffer, temp);
			 sprintf(observation_buffer2, "%s%d%s", "observation Item_O_", idx,"= ([");

			for (int i = 0; i < colcount; i++)
			{
				char* name = sqlite3_column_name(stmt, i);
				strcat(observation_buffer2, " ");
				strcat(observation_buffer2, name);
				strcat(observation_buffer2, ":");
				char* value = sqlite3_column_text(stmt, i);
				strcat(observation_buffer2, " ");
				strcat(observation_buffer2, "\"");
				strcat(observation_buffer2, value);	
				strcat(observation_buffer2, "\"");
				strcat(observation_buffer2, ",");

			}
			 
			observation_buffer2[strlen(observation_buffer2) - 1] = '\0';
			strcat(observation_buffer2, " ], 1, 0, 1.0);\r\n"); 
			 
			idx++; 
			 
			observation_buffer3= strAppendPointer(observation_buffer3, observation_buffer2);
			 
		}

		observation_buffer[strlen(observation_buffer) - 1] = '\0';

		strcat(observation_buffer, " \r\n };\r\n");
		strcat(observation_buffer, observation_buffer3);

	}
	 else
	 {

		 sprintf(observation_buffer, "%s", sqlite3_errmsg(db));
	 }
	 sqlite3_finalize(stmt); 

	
	 char* result = malloc(strlen(observation_buffer) + 1);
	 strcpy(result, observation_buffer);
	  
	 sqlite3_result_text(context, result, strlen(result), &freeResult);

}


#ifdef _WIN32
__declspec(dllexport)
#endif

int sqlite3_extension_init(sqlite3* db, char** error, const sqlite3_api_routines* api)
{
	SQLITE_EXTENSION_INIT2(api);

	sqlite3_create_function(db, "ForensicLucid", 1 , SQLITE_ANY,
									NULL, Flucidencoder, NULL, NULL);

	return SQLITE_OK;
}


