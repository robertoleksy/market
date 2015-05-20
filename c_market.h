#ifndef C_MARKET_H
#define C_MARKET_H

#include <map>
#include <vector>
#include <iostream>
#include "c_user.h"

enum class e_currency {
  USD,
  BTC
};

class c_user;

class c_market
{
public:
  c_market() = default;
  c_market(const c_market & mark) = delete;
  c_market & operator = (const c_market &) = delete;
  ~c_market();
  void buy(e_currency currency, unsigned int nuber_of, unsigned int ID, unsigned int price);
  void sell(e_currency currency, unsigned int nuber_of, unsigned int ID, unsigned int price);
  unsigned int get_current_price();
  void add_user(std::shared_ptr<c_user> new_user);
  void run();
private:
  struct s_bid {
    unsigned int ID;
    unsigned int number_of_tokens;
  };
  std::map<unsigned int, std::vector<s_bid>> m_market_map_sell; // price => s_bid
  std::map<unsigned int, std::vector<s_bid>> m_market_map_buy;
  unsigned int m_last_price = 1000;
  unsigned int m_number_of_btc = 0;
  unsigned int m_number_of_usd = 0;
  std::map<unsigned int, std::shared_ptr<c_user>> m_users_map; // ID => ptr
};

#endif // C_MARKET_H
