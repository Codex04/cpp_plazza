/*
** Email.cpp for cpp_plazza in /Users/metge_q/rendu/cpp_plazza/Srcs/Scrapper
**
** Made by Quentin Metge
** Login   <metge_q@epitech.net>
**
** Started on  Fri Apr 28 10:15:04 2017 Quentin Metge
** Last update Sat Apr 29 14:31:12 2017 Quentin Metge
*/

#include "Scrapper.hpp"

namespace plazza
{

  std::string       Scrapper::beforeAt(std::string const& buffer, int i){
    std::string     word = "";

    if (i - 1 >= 0 && this->_printable.find_first_of(buffer[--i]) != std::string::npos){
      for (int j = 0; i >= 0 && j < 65 && this->_printable.find_first_of(buffer[i]) != std::string::npos; j++){
        word += buffer[i--];
      }
    }
    else
      return ("");
    return (std::string(word.rbegin(), word.rend()));
  }

  std::string       Scrapper::afterAt(std::string const& buffer, size_t i){
    std::string     word = "";

    if (buffer[i + 1] && this->_printable.find_first_of(buffer[++i]) != std::string::npos){
      word += buffer[i++];
      for (int j = 0; buffer[i] && j < 256 && this->_printable.find_first_of(buffer[i]) != std::string::npos; j++){
        word += buffer[i++];
      }
    }
    else
      return ("");
    return (word);
  }

  void              Scrapper::dispEmail(std::string const& buffer){
    std::string         wordBefore = "";
    std::string         wordAfter = "";
    size_t              found = buffer.find_first_of('@');

    while (found != std::string::npos){
      if (!(wordBefore = beforeAt(buffer, found)).empty()){
          if (!(wordAfter = afterAt(buffer, found)).empty()){
            this->dispResult(wordBefore + '@' + wordAfter);
          }
      }
      found = buffer.find_first_of('@', found + 1);
    }
  }

}
