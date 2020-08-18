

/// This dll extension is for DB Browser for SQLite to generate FLucid from tables
///// https://sqlitebrowser.org/


#include <stdio.h>
#include <assert.h>
#include "sqlite3ext.h"
#define MAX_SYNTAX_SIZE 2500


SQLITE_EXTENSION_INIT1;

#include <stdlib.h>
 
void freeResult(void* ptr)
{
	if (ptr != NULL)
		free(ptr);
	return;
}




static void Flucidencoder(sqlite3_context* context, int argc, sqlite3_value** argv) {
	 
	assert(argc == 1);

	const char* tablename = sqlite3_value_text(argv[0]);
	char observation_syntax_buffer[MAX_SYNTAX_SIZE] = "observation sequence ";
	 
	strcat(observation_syntax_buffer, tablename);
	strcat(observation_syntax_buffer, " { ");
	strcat(observation_syntax_buffer, " }\0");

	 char* result = malloc(strlen(observation_syntax_buffer)+1);
     strcpy(result, observation_syntax_buffer);
	 
	 

	 printf("%s\n", result);
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



 