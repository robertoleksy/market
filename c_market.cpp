#include "c_market.h"

void c_market::buy(e_currency currency, unsigned int nuber_of, unsigned int ID, unsigned int price)
{
  if (m_market_map.find(price) == m_market_map.end()) { // not found
    m_market_map[price] = std::move(std::vector<s_bid>());
  }
  s_bid bid {ID, nuber_of, s_bid::e_kind_of_bid::buy};
  m_market_map.at(price).push_back(bid);
}

void c_market::sell(e_currency currency, unsigned int nuber_of, unsigned int ID, unsigned int price)
{

}

unsigned int c_market::get_current_price()
{
  return m_last_price;
}

void c_market::add_user(std::shared_ptr< c_user > new_user)
{
  m_users_vector.emplace_back(std::move(new_user));
}
