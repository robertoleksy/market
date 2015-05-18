#ifndef C_USER_H
#define C_USER_H

#include <random>
#include <memory>
#include "c_market.h"

class c_market;
enum class e_currency;

class c_user
{
public:
  c_user(unsigned int ID, std::shared_ptr<c_market> market_ptr);
  void add_money(unsigned int number_of, e_currency currency);
  unsigned int get_ID();
private:
  struct s_money {
    e_currency currency;
    unsigned int number_of;
  };
  s_money m_money_USD;
  s_money m_money_BTC;
  unsigned int m_ID;
  std::shared_ptr<c_market> m_market_ptr;
  std::default_random_engine m_rand_generator;
  void buy();
  void sell();
};

#endif // C_USER_H