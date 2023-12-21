#ifndef _PARSER_H_
#define _PARSER_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

static const char *WHITESPACE = " \t\n\r";

class Parser
{
private:
   vector<std::string> token;

public:
   Parser(std::string line)
   {
      std::stringstream is;
      trim_whitespace(line);
      if (line.empty())
         return;
      is.str(line);
      std::string tok;
      do {
         if (!(is >> tok))
            break;
         if (tok[0] == '"')
         { // read until end quote
            tok = tok.substr(1, tok.size() - 1);
            if (tok[tok.length() - 1] == '"')
               tok.erase(tok.size() - 1);
            else
            {
               std::string rest;
               if (!getline(is, rest, '"'))
               {
                  cout << "Missing end quote" << endl;
                  break;
               }
               tok = tok + rest;
            }
         }
         token.push_back(tok);
      } while (1);
   }

   unsigned numArgs() const
   {
      return (token.size() - 1);
   }

   std::string getOperation()
   {
      if (token.size() == 0)
         return ("");
      return token[0];
   }

   std::string getArg(unsigned int argnum) const
   {
      if (argnum >= token.size())
         return ("");
      return token[argnum];
   };

   static std::string splitFirst(std::string &s)
   {
      s.erase(0, s.find_first_not_of(WHITESPACE));
      std::string first;
      std::stringstream is(s);
      is >> first;
      s.erase(0, s.find_first_of(WHITESPACE));
      return first;
   }

   static void trim_whitespace(std::string &s)
   {
      s.erase(0, s.find_first_not_of(WHITESPACE));
      s.erase(s.find_last_not_of(WHITESPACE) + 1);
   }

   static bool isInteger(const std::string &str)
   {
      for (const char &c : str)
         if (!std::isdigit(c))
            return false;
      return true;
   }
};

#endif
