#include "c_market.h"

c_market::~c_market()
{
  std::cout << "market destructor" << std::endl;
}

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
  std::map<unsigned int, std::vector<s_bid>>::iterator it_last_buy = m_market_map_buy.end();
  it_last_buy--;
  std::map<unsigned int, std::vector<s_bid>>::iterator it_first_sell = m_market_map_sell.begin();
  unsigned int tokens_for_seller; // USD
  unsigned int tokens_for_buyer; // BTC
  s_bid seller_bid, buyer_bid;
  while (it_last_buy->first >= it_first_sell->first && (!(m_market_map_buy.empty() || m_market_map_sell.empty()))) {
    seller_bid = it_first_sell->second.front();
    buyer_bid = it_last_buy->second.front();
    if (buyer_bid.number_of_tokens == seller_bid.number_of_tokens) { // tokens in buy bid == tokens in sell bid
      tokens_for_seller = buyer_bid.number_of_tokens * it_last_buy->first; // BTC * price
      tokens_for_buyer = seller_bid.number_of_tokens;
      m_users_map.at(buyer_bid.ID)->add_money(tokens_for_buyer, e_currency::BTC);
      m_users_map.at(seller_bid.ID)->add_money(tokens_for_seller, e_currency::USD);
      m_last_price = it_last_buy->first;

      std::cout << "Done transaction: User " << it_last_buy->second.front().ID << " bought from User " << it_first_sell->second.front().ID 
      << ' ' << it_first_sell->second.front().number_of_tokens << " tokens for " << m_last_price << std::endl;
      m_market_map_buy.erase(it_last_buy);
      m_market_map_sell.erase(it_first_sell);
      
    }
    
    else if (buyer_bid.number_of_tokens > seller_bid.number_of_tokens) { // tokens in buy bid > tokens in sell bid
      tokens_for_seller = buyer_bid.number_of_tokens;
      tokens_for_buyer = seller_bid.number_of_tokens - tokens_for_seller;
      it_last_buy->second.front().number_of_tokens -= tokens_for_seller;
      tokens_for_seller *= it_last_buy->first; // BTC * price
      m_users_map.at(buyer_bid.ID)->add_money(tokens_for_buyer, e_currency::BTC);
      m_users_map.at(seller_bid.ID)->add_money(tokens_for_seller, e_currency::USD);
      m_last_price = it_last_buy->first;
      
      std::cout << "Done transaction: User " << buyer_bid.ID << " bought from User " << seller_bid.ID 
      << ' ' << seller_bid.number_of_tokens << " tokens for " << m_last_price << std::endl;
      m_market_map_sell.erase(it_first_sell);
    }
    
    else { // tokens in buy bid < tokens in sell bid
      tokens_for_seller = buyer_bid.number_of_tokens;
      tokens_for_buyer = seller_bid.number_of_tokens - tokens_for_seller;
      it_first_sell->second.front().number_of_tokens -= tokens_for_seller;
      tokens_for_seller *= it_last_buy->first;
      
      m_users_map.at(buyer_bid.ID)->add_money(tokens_for_buyer, e_currency::BTC);
      m_users_map.at(seller_bid.ID)->add_money(tokens_for_seller, e_currency::USD);
      
      m_last_price = it_last_buy->first;
      std::cout << "Done transaction: User " << it_last_buy->second.front().ID << " bought from User " << it_first_sell->second.front().ID 
      << ' ' << it_first_sell->second.front().number_of_tokens << " tokens for " << m_last_price << std::endl;
      m_market_map_buy.erase(it_last_buy);
    }
    
    if (m_market_map_sell.empty() || m_market_map_buy.empty()) {
      break;
    }
      it_last_buy = m_market_map_buy.end();
      it_last_buy--;
      it_first_sell = m_market_map_sell.begin();
      
  }
}
