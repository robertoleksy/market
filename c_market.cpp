#include "c_market.h"

void c_market::buy(e_currency currency, unsigned int nuber_of, unsigned int ID, unsigned int price)
{
  if (m_market_map_buy.find(price) == m_market_map_buy.end()) { // not found
    m_market_map_buy[price] = std::move(std::vector<s_bid>());
  }
  s_bid bid {ID, nuber_of};
  m_market_map_buy.at(price).push_back(bid);
}

void c_market::sell(e_currency currency, unsigned int nuber_of, unsigned int ID, unsigned int price)
{
  if (m_market_map_sell.find(price) == m_market_map_sell.end()) { // not found
    m_market_map_sell[price] = std::move(std::vector<s_bid>());
  }
  s_bid bid {ID, nuber_of};
  m_market_map_sell.at(price).push_back(bid);
}

unsigned int c_market::get_current_price()
{
  return m_last_price;
}

void c_market::add_user(std::shared_ptr< c_user > new_user)
{
 m_users_map[new_user->get_ID()] = std::move(new_user);
}

void c_market::run()
{
  std::cout << "market run" << std::endl;
  std::cout << "m_users_map size " << m_users_map.size() << std::endl;
  std::map<unsigned int, std::vector<s_bid>>::iterator it_last_buy = --m_market_map_buy.end();
  std::map<unsigned int, std::vector<s_bid>>::iterator it_first_sell = m_market_map_sell.begin();
  while (it_last_buy->first >= it_first_sell->first && !(m_market_map_buy.empty() || m_market_map_sell.empty())) {
    if (it_last_buy->second.front().number_of_tokens == it_first_sell->second.front().number_of_tokens) { // buy bid == sell bid
      std::cout << "add money for ID " << it_last_buy->second.front().ID << std::endl;
      std::cout << "add " << it_first_sell->second.front().number_of_tokens << "$" << std::endl;
      m_users_map.at(it_last_buy->second.front().ID)->add_money(it_first_sell->second.front().number_of_tokens, e_currency::USD);
      m_last_price = it_last_buy->first;
      m_market_map_buy.erase(it_last_buy);
      m_market_map_sell.erase(it_first_sell);
      std::cout << "Done transaction: User " << it_last_buy->second.front().ID << " bought from User " << it_first_sell->second.front().ID 
	   << ' ' << it_first_sell->second.front().number_of_tokens << " tokens for " << m_last_price << std::endl;
    }
    else if (it_last_buy->second.front().number_of_tokens > it_first_sell->second.front().number_of_tokens) { // buy bid > sell bid
      std::cout << "add money for ID " << it_last_buy->second.front().ID <<std::endl;
      std::cout << "add " << it_first_sell->second.front().number_of_tokens << "$" << std::endl;
      m_users_map.at(it_last_buy->second.front().ID)->add_money(it_first_sell->second.front().number_of_tokens, e_currency::USD);
      it_last_buy->second.front().number_of_tokens -= it_first_sell->second.front().number_of_tokens;
      m_last_price = it_last_buy->first;
      m_market_map_sell.erase(it_first_sell);
      std::cout << "Done transaction: User " << it_last_buy->second.front().ID << " bought from User " << it_first_sell->second.front().ID 
      << ' ' << it_first_sell->second.front().number_of_tokens << " tokens for " << m_last_price << std::endl;
    }
    else { // buy bid < sell bid
      std::cout << "add money for ID " << it_last_buy->second.front().ID <<std::endl;
      std::cout << "add " << it_last_buy->second.front().number_of_tokens << std::endl;
      m_users_map.at(it_last_buy->second.front().ID)->add_money(it_last_buy->second.front().number_of_tokens, e_currency::USD);
      it_first_sell->second.front().number_of_tokens -= it_last_buy->second.front().number_of_tokens;
      m_last_price = it_last_buy->first;
      m_market_map_sell.erase(it_last_buy);
      std::cout << "Done transaction: User " << it_last_buy->second.front().ID << " bought from User " << it_first_sell->second.front().ID 
      << ' ' << it_first_sell->second.front().number_of_tokens << " tokens for " << m_last_price << std::endl;
    }
    it_last_buy = --m_market_map_buy.end();
    it_first_sell = m_market_map_sell.begin();
  }
}
