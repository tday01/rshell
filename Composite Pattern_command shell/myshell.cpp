#include <iostream>
#include <cstdlib>
#include <string>
#include <string.h>
#include <cctype>
#include <vector>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


using namespace std;



// Abstract class, only provides interface for commands.
class CommandsChain
{
public:
    virtual ~CommandsChain() { }

    // Set next command in chain
    virtual void setNextCommand(CommandsChain* command) = 0;

    // Execute (or not) command based on information of status of previous command
    virtual void execute(bool succeeded) = 0;

    // Execute command. Call this method on first command in chain
    // (all next commands will be executed automatically if necessary)
    void execute()
    {
        execute(true);
    }
};



// Concrete class. Its only purpose is to signal that no more commands are in chain
class EndOfChain: public CommandsChain
{
public:
    EndOfChain()
    { }
    virtual ~EndOfChain()
    { }
    virtual void execute(bool succeeded)
    { }
    virtual void setNextCommand(CommandsChain* command)
    { }
};



// Concrete class (for initial command and commands preceeded with ';').
// Executes command always.
class Command: public CommandsChain
{
protected:
    CommandsChain* nextCommand;

private:
    string executable;
    vector<string> arguments;

public:
    Command(string& command): nextCommand(new EndOfChain), executable(command)
    { }

    virtual ~Command()
    {
        delete nextCommand;
    }

    virtual void addArgument(string& argument)
    {
        arguments.push_back(argument);
    }

    virtual void execute(bool succeeded)
    {
        // Check if command is "exit"
        if (executable == "exit")
        {
            // Don't process the rest of commands, just close program.
            exit(EXIT_SUCCESS);
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
        
        // Fork
        pid_t pid = fork();
        if (pid == 0)
        {
            // Child process.
            execvp(executable.c_str(), list);
            // If exec failed, close child process with failure exit code
            // to inform parent process about failure
            exit(EXIT_FAILURE);
        }
        else if (pid > 0)
        {
            // Parent process.
            // Wait for child process
            int status;
            waitpid(pid, &status, 0);
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
        nextCommand->execute(succeeded);
    }

    virtual void setNextCommand(CommandsChain* command)
    {
        nextCommand = command;
    }
};



// Concrete class (for commands preceeded with '&&').
// Executes command and rest of commands only if previous command succeeded.
class CommandOnSuccess: public Command
{
public:
    CommandOnSuccess(string& command): Command(command)
    { }

    virtual void execute(bool succeeded)
    {
        if (succeeded)
        {
            Command::execute(succeeded);
        }
        else
        {
        	nextCommand->execute(false);
        }
    }
};



// Concrete class (for commands preceeded with '||').
// Executes command and rest of commands only if previous command failed.
class CommandOnFail: public Command
{
public:
    CommandOnFail(string& command): Command(command)
    { }

    virtual void execute(bool succeeded)
    {
        if (!succeeded)
        {
            Command::execute(succeeded);
        }
        else
        {
        	nextCommand->execute(false);
        }
    }
};



// Find position of next token in line starting with begin position
int getNextTokenPosition(string& line, unsigned int begin)
{
    // Skip spaces
    while (begin < line.length())
    {
        if (isspace(line[begin]))
        {
            begin++;
        }
        else
        {
            break;
        }
    }
    return begin;
}



// Measures length of token, which starts at begin position
int getTokenLength(string& line, unsigned int begin)
{
    if (begin >= line.length())
    {
        return 0;
    }

    // ';' and '#' are special tokens
    if (line[begin] == ';' || line[begin] == '#')
    {
        return 1;
    }

    // All other tokens end by space or ';'
    unsigned int end = begin;
    while (end < line.length())
    {
        if (isspace(line[end]) || line[end] == ';' || line[end] == '#')
        {
            break;
        }
        else
        {
            end++;
        }
    }
    return end - begin;
}



// Parse line into sequence of commands
CommandsChain* parseCommands(string& line)
{
    CommandsChain* chain;
    Command* lastCommand;

    // Get first command name
    unsigned int begin = getNextTokenPosition(line, 0);
    unsigned int length = getTokenLength(line, begin);
    string cmd;

    // Check that at least one token is given
    if (length > 0)
    {
        // Initiate chain of commands with first command
        cmd = line.substr(begin, length);
        chain = lastCommand = new Command(cmd);
        // Read next token
        begin = getNextTokenPosition(line, begin + length);
        length = getTokenLength(line, begin);
    }
    while (begin < line.length())
    {
        // Determine type of last read token.
        string s = line.substr(begin, length);
        if (s == "#")
        {
            // Ignore the rest of line
            break;
        }
        else if (s == ";" || s == "&&" || s == "||")
        {
            // Last read token is connector.
            // Read next token an interpret it as command name
            begin = getNextTokenPosition(line, begin + length);
            length = getTokenLength(line, begin);
            if (length > 0)
            {
                cmd = line.substr(begin, length);
                if (cmd == "#")
                {
                    break;
                }
                Command* nextCommand;
                switch (s[0])
                {
                    case '&':
                        nextCommand = new CommandOnSuccess(cmd);
                        break;
                    case '|':
                        nextCommand = new CommandOnFail(cmd);
                        break;
                    default:
                        nextCommand = new Command(cmd);
                }
                lastCommand->setNextCommand(nextCommand);
                lastCommand = nextCommand;
            }
            // else command line is incomplete.
        }
        else
        {
            // Last read token is argument to command
            lastCommand->addArgument(s);
        }

        // Read next token
        begin = getNextTokenPosition(line, begin + length);
        length = getTokenLength(line, begin);
    }

    return chain;
}




int main(int argc, char* argv[])
{
    string line;
    CommandsChain* chain;
    while (true)
    {
        cout << "$ ";
        getline(cin, line);
        chain = parseCommands(line);
        if (chain != NULL)
        {
            chain->execute();
            delete chain;
        }
    }
    return EXIT_SUCCESS;
}
