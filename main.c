#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LINE 80 /* The maximum length command */

int main() {
    char *args[MAX_LINE/2 + 1]; /* an array of character strings */
    int should_run = 1; /* flag to determine when to exit program */
    int id_hist[10]={0};
    char* command_hist[10]={NULL};
    int num_hist=0;
    while (should_run) {
        printf("CSCI3120>");
        fflush(stdout);

        char input[MAX_LINE];
        char cmd[MAX_LINE];
        fgets(input, MAX_LINE, stdin);
        input[strcspn(input, "\n")] = 0;//take input

        if((strcmp(input,"history")==0||(input[0]=='!'))&&num_hist==0){
            printf("No command in history!\n");
            continue;
        }
        if(strcmp(input,"history")==0&&num_hist!=0){
            printf("ID\tPID\tCommand\n");
            if(args[1]==NULL){
                for(int k=0;k<num_hist&&k<10;k++){
                    printf("%d\t%d\t%s\n",k,id_hist[k],command_hist[k]);
                }
            }
            fflush(stdout);
            continue;
        }
        if(strcmp(input,"!!")==0&&num_hist!=0){
            printf("%s\n",command_hist[0]);
            strcpy(input,command_hist[0]);
        }
        else if((char) input[0]=='!'&&isdigit((char) input[1])&&num_hist!=0){
            //"Such a command is NOT in history!"
            if((char) input[2]=='0'){
                if(num_hist<9){
                    printf("Such a command is NOT in history!\n");
                    continue;
                }
                printf("%s\n",command_hist[9]);
                strcpy(input,command_hist[9]);
            }
            else if((char) input[2]!='\000'){
                printf("Invalid input!\n");
                continue;
            }
            else{
                int num = (char)input[1] - '0';
                if(num_hist>num-1){
                    printf("%s",command_hist[num-1]);
                    strcpy(input,command_hist[num-1]);
                }else{
                    printf("Such a command is NOT in history!\n");
                    continue;
                }
            }
            printf("\n");
        }
        fflush(stdout);
        strcpy(cmd,input);

        char *token;
        token = strtok(input, " ");
        int i = 0;
        while (token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " ");
        }
        args[i] = NULL; //spilt and push token to args

        if(strcmp(args[0],"exit")==0){
            should_run=0;
            continue;
        }

        pid_t pid = fork();
        if (pid == 0) {
            // Child process
            if(execvp(args[0], args)==-1)
                //"Invalid command!"
                printf("Invalid command!\n");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL);
            int z = num_hist;
            if(z>9)
                z=9;
            for (int x = z; x >0; x--) {
                id_hist[x]=id_hist[x-1];
                command_hist[x]=strdup(command_hist[x-1]);
            }
            id_hist[0]=pid;
            command_hist[0]= strdup(cmd);
            num_hist++;
        }
    }
    return 0;
}
