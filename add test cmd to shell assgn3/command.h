#ifndef command_H
#define command_H
#include <stdio.h>
#include <iostream>
#include <sys/wait.h>
#include <cstdlib>
#include <unistd.h>
#include <cstring>
#include <string>
#include <string.h>
#include <sys/types.h>
#include <vector>

using namespace std;

// Abstract class, only provides interface for commands.
class CommandsChain
{
protected:
    string connectedBy;

public:
    CommandsChain(): connectedBy(";")
    { }

    virtual ~CommandsChain() { }

    void setConnection(string connector)
    {
        connectedBy = connector;
    }
    
    // Set next command in chain
    virtual void setNextCommand(CommandsChain* command) = 0;
    
    // Execute (or not) command based on information of status of previous
    // command.
    // Returns true if exit was requested
    virtual bool execute(bool& succeeded) = 0;
    
    // Execute command. Call this method on first command in chain
    //(all next commands will be executed automatically if necessary)
    bool execute()
    {
        bool success = true;
        return execute(success);
    }
};

// Class only purpose is to signal that no more commands are in chain
class EndOfChain: public CommandsChain
{
public:
    EndOfChain() { }
    
    virtual ~EndOfChain() { }
    
    virtual bool execute(bool& succeeded)
    {
        return false;
    }
    
    virtual void setNextCommand(CommandsChain* command) { }
};

// For initial command and commands preceeded with ';'.
// Executes command always.
class Command: public CommandsChain
{
protected:
    CommandsChain* nextCommand;
    
private:
    string executable;
    vector<string> arguments;

    bool test();
    bool testExist(const char * path);
    bool testFile(const char * path);
    bool testDir(const char * path);
    
public:
    Command(string& command): nextCommand(new EndOfChain),
        executable(command) { }
    
    virtual ~Command()
    {
        delete nextCommand;
    }
    
    void addArgument(string& argument)
    {
        arguments.push_back(argument);
    }
    
    bool execute(bool& succeeded);

    void setNextCommand(CommandsChain* command)
    {
        nextCommand = command;
    }
};
/*
//--------------------Connectors---------------------//

// Concrete class (for commands preceeded with '&&').
// Executes command and rest of commands only if previous command succeeded.
class CommandOnSuccess: public Command
{
public:
    CommandOnSuccess(string& command): Command(command)
    { }
    
    virtual bool execute(bool& succeeded)
    {
        if (succeeded)
        {
            return Command::execute(succeeded);
        }
        else
        {
            return nextCommand->execute(succeeded);
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
    
    virtual bool execute(bool& succeeded)
    {
        if (!succeeded)
        {
            return Command::execute(succeeded);
        }
        else
        {
            succeeded = false;
            return nextCommand->execute(succeeded);
        }
    }
};
*/

// Concrete class (for sequence of commands inside parentheses "(...)").
class CommandGroup: public CommandsChain
{
private:
    CommandsChain* insideParentheses;
    CommandsChain* afterParetneses;

public:
    CommandGroup(CommandsChain* inside): insideParentheses(inside),
        afterParetneses(new EndOfChain) { }

    virtual ~CommandGroup()
    {
        delete insideParentheses;
        delete afterParetneses;
    }

    virtual void setNextCommand(CommandsChain* command)
    {
        afterParetneses = command;
    }

    bool execute(bool& succeeded)
    {
        if (connectedBy == "&&")
        {
            if (succeeded)
            {
                if (insideParentheses->execute(succeeded))
                {
                    return true; // Exit requested
                }
            }
            return afterParetneses->execute(succeeded);
        }
        else if (connectedBy == "||")
        {
            if (!succeeded)
            {
                if (insideParentheses->execute(succeeded))
                {
                    return true; // Exit requested
                }
            }
            return afterParetneses->execute(succeeded);
        }
        else {
            if (insideParentheses->execute(succeeded))
            {
                return true; // Exit requested
            }
            return afterParetneses->execute(succeeded);
        }
    }
};

#endif  // command_h
