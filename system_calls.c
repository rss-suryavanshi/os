#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/wait.h> 
int main() {

    int fd = open("example.txt",O_CREAT|O_WRONLY|O_TRUNC,S_IRUSR|S_IWUSR);
    if(fd==-1) {
        perror("There is a problem.");
        return 1;
    }

    char *text = "Hey there this is the file that is the example where we are making the use of some of the system calls for the Operating System Lab Examination.";
    ssize_t wr = write(fd,text,50);

    if(wr == -1) {
        perror("There was a problem in writing on the file.");
        close(fd);
        return 1;
    }

    pid_t pid = fork();
    if(pid==-1) {
        perror("There is a problem in forking the process.");
        return 1;
    }

    if(pid==0){
        printf("This is the child process and there is something to read from the example.txt file.");
        fd = open("example.txt",O_RDONLY);
        if(fd==-1){
            perror("There is a problem.");
            return 1;
        }
        char buffer [50] = {0};
        ssize_t rd = read(fd,buffer,50);
        if (rd == -1){
            perror("There is a problem in reading the file and putting it in the buffer.");
            close(fd);
            exit(1);
        } 
        printf("The buffer reads:%s\n",buffer);
        close(fd);
        exit(1);
    }  else {
        printf("This is the parent process and the pid of the process is:%d\n",getpid());
        wait(NULL);
        printf("The child process if finished.");
    }
    

    time_t current_time = time(NULL);
    if (current_time == -1) {
        perror("The time could not be fetched from the system.\n");
        return 1;
    }
    printf("The current time from the system is:%s\n",ctime(&current_time));

    return 0;

}
