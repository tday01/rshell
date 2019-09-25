#include "command.h"
#include <stdio.h>
#include <iostream>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <vector>
#include <cstring>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


using namespace std;

bool Command::test()
{
    if (arguments.size() == 0)
    {
        return false;
    }
    if (arguments[0] == "-e")
    {
        if (arguments.size() < 2)
        {
            return false;
        }
        return testExist(arguments[1].c_str());
    }
    else if (arguments[0] == "-f")
    {
        if (arguments.size() < 2)
        {
            return false;
        }
        return testFile(arguments[1].c_str());
    }
    else if (arguments[0] == "-d")
    {
        if (arguments.size() < 2)
        {
            return false;
        }
        return testDir(arguments[1].c_str());
    }
    // Default is '-e'
    return testExist(arguments[0].c_str());
}

bool Command::testExist(const char* path)
{
    struct stat info;
    if (stat(path, &info))
    {
        cout << "(FALSE)" << endl;
        return false;
    }
    cout << "(TRUE)" << endl;
    return true;
}

bool Command::testFile(const char * path)
{
    struct stat info;
    if (stat(path, &info))
    {
        cout << "(FALSE)" << endl;
        return false;
    }
    if (S_ISREG(info.st_mode))
    {
        cout << "(TRUE)" << endl;
        return true;
    }
    cout << "(FALSE)" << endl;
    return false;
}

bool Command::testDir(const char * path)
{
    struct stat info;
    if (stat(path, &info))
    {
        cout << "(FALSE)" << endl;
        return false;
    }
    if (S_ISDIR(info.st_mode))
    {
        cout << "(TRUE)" << endl;
        return true;
    }
    cout << "(FALSE)" << endl;
    return false;
}

bool Command::execute(bool& succeeded)
{
    if (succeeded && connectedBy == "||")
    {
        return nextCommand->execute(succeeded);
    }
    if (!succeeded && connectedBy == "&&")
    {
        return nextCommand->execute(succeeded);
    }

    // Check if command is "exit"
    if (executable == "exit")
    {
        // Don't process the rest of command, exit requested
        return true;
    }

    // Check if command is "test"
    if (executable == "test")
    {
        succeeded = test();
        return nextCommand->execute(succeeded);
    }

    // Prepare argument list
    char** list = new char*[arguments.size() + 2];
    list[0] = new char[executable.length()+1];
    strcpy(list[0], executable.c_str());
    for (unsigned int i = 0; i < arguments.size(); i++)
    {
        list[i+1] = new char[arguments[i].length()+1];
        strcpy(list[i+1], arguments[i].c_str());
    }
    list[arguments.size()+1] = NULL;

    // Prepare pipe if neeeded
    int fd[2];
    if (outputRedirectionMode == RM_PIPE)
    {
        if (pipe(fd) < 0)
        {
            perror("Pipe Failure");
            succeeded = false;
        }
        if (dynamic_cast<Command*>(nextCommand) != NULL)
        {
            dynamic_cast<Command*>(nextCommand)->pipeIn = fd[0];
        }
    }

    // Fork
    pid_t pid;
    if ((pid = fork()) == -1)
    {
        perror ("Fork Failure");
    }
    if (pid == 0)
    {
        // Child process.

        // First, setup the redirections
        if (inputRedirectionMode == RM_PIPE)
        {
            if (dup2(pipeIn, STDIN_FILENO) < 0)
            {
                perror("Failed to pipe the input stream");
                exit(EXIT_FAILURE);
            }
            close(pipeIn);
        }
        if (inputRedirectionMode == RM_SIMPLE)
        {
            // Open the input file
            int fileHandle = open(inputFileName.c_str(), O_RDONLY);

            // Redirect the stream and validate the result
            if (fileHandle < 0 || dup2(fileHandle, STDIN_FILENO) < 0)
            {
                perror("Failed to redirect the input stream");
                exit(EXIT_FAILURE);
            }

            // Close the file, and only leave stream
            close(fileHandle);
        }
        if (outputRedirectionMode == RM_PIPE)
        {
            if (dup2(fd[1], STDOUT_FILENO) < 0)
            {
                perror("Failed to pipe the output stream");
                exit(EXIT_FAILURE);
            }
            close(fd[1]);
        }
        if (outputRedirectionMode == RM_SIMPLE || outputRedirectionMode == RM_APPEND)
        {
            // Determine the flags to open output file
            int flags = O_WRONLY | O_CREAT;
            if (outputRedirectionMode == RM_SIMPLE)
            {
                flags |= O_TRUNC;
            }
            else // RM_APPEND
            {
                flags |= O_APPEND;
            }

            // Open the output file
            int fileHandle = open(outputFileName.c_str(), flags, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

            // Redirect the stream and validate the result
            if (fileHandle < 0 || dup2(fileHandle, STDOUT_FILENO) < 0)
            {
                printf("%d", fileHandle);
                perror("Failed to redirect the output stream");
                exit(EXIT_FAILURE);
            }

            // Close the file, and only leave stream
            close(fileHandle);
        }

        // Run the actual executable
        if ((execvp(executable.c_str(), list)) == -1)
        {
            perror ("Child Failure");
        }
        // If exec failed, close child process with failure exit code
        // to inform parent process about failure
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        // Parent process.
        // Wait for child process
        int status;
        if ((waitpid(pid, &status, 0)) == -1)
        {
            perror ("Child End Status Failure");
        }

        // Close the pipe
        if (outputRedirectionMode == RM_PIPE)
        {
            close(fd[1]);
        }

        // Find out how child process ended
        if (WIFEXITED(status) && WEXITSTATUS(status) == EXIT_SUCCESS)
        {
            succeeded = true;
        }
        else
        {
            succeeded = false;
        }
    }
    else
    {
        // Fork failed.
        succeeded = false;
    }

    // Release memory
    for (unsigned int i = 0; i <= arguments.size(); i++)
    {
        delete list[i];
    }
    delete[] list;

    // Execute next command in chain
    return nextCommand->execute(succeeded);
}
