#ifndef C_MARKET_H
#define C_MARKET_H

#include <map>
#include <vector>
#include "c_user.h"

enum class e_currency {
  USD,
  BTC
};

class c_user;

class c_market
{
public:
  c_market() = delete;
  c_market(const c_market & mark) = delete;
  c_market & operator = (const c_market &) = delete;
  void buy(e_currency currency, unsigned int nuber_of, unsigned int ID, unsigned int price);
  void sell(e_currency currency, unsigned int nuber_of, unsigned int ID, unsigned int price);
  unsigned int get_current_price();
  void add_user(std::shared_ptr<c_user> new_user);
  void run(); // TODO thread
private:
  struct s_bid {
    unsigned int ID;
    unsigned int number_of_tokens;
  };
  std::map<unsigned int, std::vector<s_bid>> m_market_map_sell;
  std::map<unsigned int, std::vector<s_bid>> m_market_map_buy;
  unsigned int m_last_price;
  std::vector<std::shared_ptr<c_user>> m_users_vector;
};

#endif // C_MARKET_H
