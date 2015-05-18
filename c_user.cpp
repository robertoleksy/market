#include "c_user.h"

c_user::c_user(unsigned int ID, std::shared_ptr<c_market> market_ptr)
:
m_ID(ID),
m_market_ptr(market_ptr)
{
  m_money_USD.currency = e_currency::USD;
  m_money_BTC.currency = e_currency::BTC;
  std::default_random_engine generator;
  std::uniform_int_distribution<unsigned int> distribution(100000, 10000000);
  m_money_BTC.number_of = distribution(generator);
  m_money_USD.number_of = distribution(generator);
}

void c_user::buy()
{
  if (m_money_USD.number_of <= m_money_BTC.number_of) {
      m_market_ptr->buy(e_currency::BTC, 100000, m_ID, m_market_ptr->get_current_price());
  }
  else {
   m_market_ptr->buy(e_currency::USD, 100000, m_ID, m_market_ptr->get_current_price());
  }
}

void c_user::sell()
{
  if (m_money_USD.number_of <= m_money_BTC.number_of) {
      m_market_ptr->sell(e_currency::BTC, 100000, m_ID, m_market_ptr->get_current_price());
  }
  else {
   m_market_ptr->sell(e_currency::USD, 100000, m_ID, m_market_ptr->get_current_price());
  }  
}
