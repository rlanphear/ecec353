
/******************************************
 * Chat Client
 *
 * Erick Weigel
 * Gerardo Faia
 *
 * Programming Assignment 3
 * Local Chat Server
 *****************************************/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "chat.h"

void prepend(char* s, const char* t)
{
    size_t len = strlen(t);
    size_t i;

    memmove(s + len, s, strlen(s) + 1);

    for (i = 0; i < len; ++i)
    {
        s[i] = t[i];
    }
}

int main(int argc, char *argv[]){
 
   // Initialize loop iterators
   int i;
   int j;

   int client_status;

   char* groupID;
   char* clientID;
   char command_line[MESSAGE_SIZE];

   char message[MESSAGE_SIZE]; 

   int server_fifo;



   if (argc != 3) {
      fprintf(stderr,"The program must have 2 arguments (groupID and clientID).\n");      
      exit(1);
   }
   else {
      groupID = argv[1];
      clientID = argv[2];
      sprintf(message, "/g %s /u %s", clientID, groupID);
   }
  
   client_status = 1;

   while(client_status){

      server_fifo = open(SERVER_PIPE, O_NONBLOCK | O_WRONLY);
      if(server_fifo < 0){
         printf("The server is not currently online, exiting.\n");
         exit(1);
      }
      else{
         write(server_fifo, &message, sizeof(message));
         printf("Sent client informtion, group %s and user %s to server.\n", groupID, clientID);
         close(server_fifo);
      }


      if(fgets(command_line, MESSAGE_SIZE, stdin) != NULL){

         // Exit Command
         if(strncmp(C_COMMAND_EXIT,command_line, 5) == 0){
            printf("Closing Server.\n");
            client_status = 0;
         }
         else{
            server_fifo = open(SERVER_PIPE, O_NONBLOCK | O_WRONLY);
            if(server_fifo < 0){
               printf("Error opening pipe.\n");
            }
            else{
               prepend(command_line,"/t ");
               write(server_fifo, &command_line, sizeof(command_line));
               printf("Wrote to file.\n");
               close(server_fifo);
           }
         }

      } 

   }
 
   return 0;
   
}



