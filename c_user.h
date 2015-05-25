#ifndef C_USER_H
#define C_USER_H

#include <random>
#include <memory>
#include <iostream>
#include <ctime>
#include <cstdlib>
#include "c_market.h"

class c_market;
enum class e_currency;

class c_user
{
public:
  c_user(unsigned int ID, std::shared_ptr<c_market> market_ptr);
  ~c_user();
  void add_money(unsigned int number_of, e_currency currency);
  unsigned int get_money(unsigned int number_of, e_currency currency);
  unsigned int get_ID();
  int get_currency_stat(e_currency currency);
  void buy(); // only BTC
  void sell(); // only BTC
private:
  struct s_money {
    e_currency currency;
    unsigned int number_of;
  };
  s_money m_money_USD;
  s_money m_money_BTC;
  unsigned int m_ID;
  c_market *m_market_ptr;
  std::minstd_rand0 m_rand_generator;

};

#endif // C_USER_H