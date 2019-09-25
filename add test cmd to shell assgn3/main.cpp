
#include <iostream>
#include <string>
#include <cctype>
#include <string.h>
#include <cstring>
#include "command.h"

//-----------------------PARSER---------------------------//
CommandsChain* parseCommand(string& line, unsigned int& begin,
    string precedingConnector);

// Remove '#' comment from line
void excludeComments(string& line)
{
    unsigned int pos = line.find('#');
    if (pos >= 0 && pos < line.length())
    {
        line = line.substr(0, pos);
    }
}

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
    
    // ';', '[', ']', '(' and ')' are special tokens
    if (line[begin] == ';' || line[begin] == '(' || line[begin] == ')' ||
            line[begin] == '[' || line[begin] == ']')
    {
        return 1;
    }
    
    // All other tokens end by space or special token
    unsigned int end = begin;
    while (end < line.length())
    {
        if (isspace(line[end]) || line[end] == ';' ||
                line[end] == ')' || line[end] == ']' ||
                line[end] == '(' || line[end] == '[')
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

// SIMPLE := command
// SIMPLE := command arglist
// This also includes "test ..." but not "[ ... ]"
// Simple command can't contain connectors or parentheses
CommandsChain* parseSimpleCommand(string& line, unsigned int& begin)
{
    unsigned int length = getTokenLength(line, begin);
    string s = line.substr(begin, length);
    if (s == ")" || s == "]" || s == ";" || s == "||" || s == "&&")
    {
        cout << "Error: Unexpected token \"" << s << "\" at position "
            << begin << endl;
        return NULL;
    }
    
    Command* command = new Command(s);
    begin = getNextTokenPosition(line, begin + length);
    length = getTokenLength(line, begin);
    while (length > 0)
    {
        s = line.substr(begin, length);
        if (s == "(" || s == ")" || s == "[" || s == "]" || s == ";" ||
                s == "||" || s == "&&")
        {
            break;
        }
        command->addArgument(s);

        begin = getNextTokenPosition(line, begin + length);
        length = getTokenLength(line, begin);
    }

    return command;
}

// TEST := '[' SIMPLE ']'
CommandsChain* parseTestCommand(string& line, unsigned int& begin)
{
    // line[begin] is '['
    // Parse until ']' is encountered
    string s = "test";
    Command* command = new Command(s);

    begin = getNextTokenPosition(line, ++begin);
    unsigned int length = getTokenLength(line, begin);
    if (length == 0)
    {
        cout << "Error: Unmatched \'[\'" << endl;
        delete command;
        return NULL;
    }
    s = line.substr(begin, length);

    while (s != "]")
    {
        if (s == "(" || s == ";" || s == "[" || s == ")" || s == "||" ||
                s == "&&")
        {
            cout << "Error: Unexpected token \"" << s << "\" inside brackets"
                << " at position " << begin << endl;
            delete command;
            return NULL;
        }
        command->addArgument(s);
        begin = getNextTokenPosition(line, begin + length);
        length = getTokenLength(line, begin);
        if (length == 0)
        {
            cout << "Error: Unmatched \'[\'" << endl;
            delete command;
            return NULL;
        }
        s = line.substr(begin, length);
    }

    begin += length;
    return command;
}

// PAREN := '(' CMD ')'
// CMD is any command, including another PAREN.
CommandsChain* parseParetheses(string& line, unsigned int& begin)
{
    // line[begin] is '('
    // Parse until ')' is encountered
    begin++;
    CommandsChain* insideParentheses = parseCommand(line, begin, ";");
    if (insideParentheses == NULL)
    {
        return NULL;
    }
    CommandGroup* group = new CommandGroup(insideParentheses);
    begin = getNextTokenPosition(line, begin);
    unsigned int length = getTokenLength(line, begin);
    if (length == 0)
    {
        delete group;
        cout << "Error: Unmatched \"(\"" << endl;
        return NULL;
    }
    if (line[begin] != ')')
    {
        delete group;
        cout << "Unmatched \"(\"" << endl;
        return NULL;
    }

    begin += length;
    return group;
}

// CMD := (SIMPLE | TEST | PAREN) [connector CMD]
CommandsChain* parseCommand(string& line, unsigned int& begin,
        string precedingConnector)
{
    CommandsChain* chain;

    if (line[begin] == '[')
    {
        chain = parseTestCommand(line, begin);
    }
    else if (line[begin] == '(')
    {
        chain = parseParetheses(line, begin);
    }
    else
    {
        chain = parseSimpleCommand(line, begin);
    }

    if (chain == NULL)
    {
        return NULL;
    }
    chain->setConnection(precedingConnector);

    begin = getNextTokenPosition(line, begin);
    unsigned int length = getTokenLength(line, begin);
    if (length == 0)
    {
        return chain;
    }

    string connector = line.substr(begin, length);
    if (connector == ")")
    {
        return chain;
    }
    if (connector != ";" && connector != "||" && connector != "&&")
    {
        cout << "Error: Unexpected token \"" << connector
            << "\" at position " << begin << endl;
        delete chain;
        return NULL;
    }

    begin = getNextTokenPosition(line, begin + length);
    length = getTokenLength(line, begin);
    if (length == 0)
    {
        cout << "Error: Unexpected end of command line" << endl;
        delete chain;
        return NULL;
    }

    CommandsChain* next = parseCommand(line, begin, connector);
    if (next == NULL)
    {
        delete chain;
        return NULL;
    }

    chain->setNextCommand(next);
    return chain;
}

CommandsChain* parseCommand(string& line)
{
    excludeComments(line);
    unsigned int begin = getNextTokenPosition(line, 0);
    return parseCommand(line, begin, ";");
}

//-----------------------END-PARSER-------------------------//

int main(int argc, char* argv[])
{
    string line;
    CommandsChain* chain;

    bool finish = false;
    while (!finish)
    {
        cout << "$ ";
        getline(cin, line);
        chain = parseCommand(line);
        if (chain != NULL)
        {
            finish = chain->execute();
            delete chain;
        }
    }
    return EXIT_SUCCESS;
}
