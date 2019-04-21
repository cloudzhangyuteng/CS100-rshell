#include "header/Shell.h"

#include <iostream>


Shell::Shell() : index(0) { }
Shell::~Shell() { }

void Shell::read_input()
{
   std::getline(std::cin, user_input);
}

void Shell::parse()
{
   input_preparation();
   tempo = "";
    
   for (size_t i = 0; i < user_input.size(); i++) {
      if (user_input[i] == '"') {
         while (true) {
            if (user_input[++i] == '"') {
               if (i == user_input.size() - 1) {
                  my_vec.push_back(tempo);
                  return;
               }
               i++;
               break;
            }
            tempo += user_input[i];
         }
      }
        
      if (user_input[i] != ' ') {
         tempo += user_input[i];
      }
      else {
         my_vec.push_back(tempo);
         tempo = "";
      }
        
      if (i == user_input.size() - 1) {
         my_vec.push_back(tempo);
      }
   }
}

void Shell::run()
{
   Base* root = create_tree();
   root->execute(0, 1);
}

void Shell::input_preparation()
{
   for (size_t i = 0; i < user_input.size(); i++) {
      if (user_input[i] == '"') {
         while (user_input[++i] != '"') {}
      }
      if (user_input[i] == '[') {
         user_input.replace(i, 1, "test");
         i += 3;
         
         while (user_input[++i] != ']') { }
         
         user_input.erase(i - 1, 2);
         i -= 2;
         if (i == user_input.size() - 1) {
            break;
         }
      }
        
      if (user_input[i] == '#') {
         user_input.erase(user_input.begin() + i, user_input.end());
         break;
      }
        
      if (user_input[i] == '(') {
         user_input.insert(i + 1, " ");
         i++;
      }
        
      if (user_input[i] == ')' || user_input[i] == ';') {
         user_input.insert(i, " ");
         i++;
      }
   }
}

Base* Shell::create_tree()
{
   Base* root = nullptr;
   Base* next;
    
   while (index < my_vec.size()) {
      if (!root) {
         if (my_vec[index] == "(") {
            index++;
            root = create_tree();
         }
         else {
            root = create_command();
         }
      }
      else {
         std::string connector = my_vec[index];
         if (connector == ")") {
            index++;
            return root;
         }
         index++;
        
         if (my_vec[index] == "(") {
            index++;
            next = create_tree();
         }
         else {
            next = create_command();
         }
        
         if (connector == "&&") {
            root = new And(root, next);
         }
         else if (connector == "||") {
            root = new Or(root, next);
         }
         else if (connector == ";") {
            root = new Semicolon(root, next);
         }
         else if (connector == "|") {
            root = new My_Pipe(root, next);
         }
         else if (connector == "<") {
            root = new My_In(root, next);
         }
         else if (connector == ">") {
            root = new My_Out(root, next);
         }
         else if (connector == ">>") {
            root = new My_Out_Append(root, next);
         }
      }
   }
   return root;
}


Base* Shell::create_command()
{
   std::vector<std::string> com_command_line;
   Base* com;
   while (index < my_vec.size()) {
      if (my_vec[index] == "&&" || my_vec[index] == "||" || my_vec[index] == ";" || my_vec[index] == ")" || my_vec[index] == "|" || my_vec[index] == "<" || my_vec[index] == ">" || my_vec[index] == ">>") {
         com = new Command(com_command_line);
         return com;
      }
      else {
         com_command_line.push_back(my_vec[index]);
      }
      index++;
   }
   com = new Command(com_command_line);
   return com;
}


// test functions
void Shell::set_input(std::string s)
{
   user_input = s;
}

std::string Shell::get_my_vec(int i)
{
   return my_vec[i];
}
