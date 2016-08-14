/******************************************
 * q
 * Chat Server
 *
 * Erick Weigel
 * Gerardo Faia
 *
 * Programming Assignment 3
 * Local Chat Server
 *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "chat.h"

#define CLIENT_MAX 10
#define GROUP_MAX 10
#define PEER_MAX 10

/* 8/13/16
 * Group Usage ID is not intializing to 0 correctly
 *
 * Client List Works
 * Group Members Works
 * 
 *
 *
 */


int main(int argc, char **argv){
 
   // Initialize loop iterators
   int i;
   int j;

   struct stat st;

   // Intialize Client List Array
   //    Can be accessed using standard array notatiom
   //       client_list[i] = "somestring"
   //
   //    Overwritting an array location is allowed
 

   char **client_list = (char**)calloc(CLIENT_MAX, sizeof(char*));
   for(i = 0; i < CLIENT_MAX; i++){
      client_list[i] = (char*)calloc(MESSAGE_SIZE, sizeof(char*));
   }

   // Intialize Group Usage Array
   //    Maintains a list of integers indicating which group slots are
   //    available.

   int *group_usage = (int*)calloc(CLIENT_MAX, sizeof(int));
   for(i = 0; i < CLIENT_MAX; i++){
      group_usage[i] = 0;
   }    

   // Initalize Group Memember list
   //    This structure is a list of lists that contain the members
   //    of each group on the server
   //
   //    group_list[0][0] = "Member 0 of group 0"

   char ***group_members = calloc(GROUP_MAX, sizeof(***group_members));
   for(i = 0; i < CLIENT_MAX; i++){
      group_members[i] = calloc(CLIENT_MAX, sizeof(char*));
   }
   for(i = 0; i < CLIENT_MAX; i++){
      for(j = 0; j < CLIENT_MAX; j++){
         group_members[i][j] = calloc(MESSAGE_SIZE, sizeof(char*));
      }
   }

   // Setup FIFO File as a pipe if it doesn't exist
   //    Defines a new special file in a temp directory
   //    SERVER_PIPE is defined in "chat.h"

   if(stat(SERVER_PIPE, &st) != 0){
      mkfifo(SERVER_PIPE, 666); 
   }

   // ---- Testing -----
   struct group_context test_context;
   test_context.group_id = "teststring\n";
   if(group_usage[0] == 0){
     group_members[0][0] = test_context.group_id;   
     group_usage[0] = 1;
   }

   printf(group_members[0][0]);
   printf("%d\n",group_usage[0]);
   free(client_list);
   free(group_usage);
   //free(group_members);

   return 0;
}
