#include "c_user.h"

c_user::c_user(unsigned int ID, std::shared_ptr<c_market> market_ptr)
:
m_ID(ID),
m_market_ptr(market_ptr)
{
  m_money_USD.currency = e_currency::USD;
  m_money_BTC.currency = e_currency::BTC;
  std::uniform_int_distribution<unsigned int> distribution(100000, 10000000);
  m_money_BTC.number_of = distribution(m_rand_generator);
  m_money_USD.number_of = distribution(m_rand_generator);
}

void c_user::buy()
{
  std::normal_distribution<float> distribution_norm(m_market_ptr->get_current_price(), 50);
  float rand = distribution_norm(m_rand_generator);
  unsigned int price = std::floor(rand + 0.5);
  std::uniform_int_distribution<int> distribution_linear(10000,100000);
  unsigned int number_of_tokens = distribution_linear(m_rand_generator);
  std::cout << "(user " << m_ID << ") buy " << number_of_tokens << std::endl;
  std::cout << "price " << price << std::endl;
  m_market_ptr->buy(e_currency::BTC, number_of_tokens, m_ID, price);
}

void c_user::sell()
{
  std::normal_distribution<float> distribution_norm(m_market_ptr->get_current_price(), 50);
  float rand = distribution_norm(m_rand_generator);
  unsigned int price = std::floor(rand + 0.5);
  std::uniform_int_distribution<int> distribution_linear(10000,100000);
  unsigned int number_of_tokens = distribution_linear(m_rand_generator);
  number_of_tokens = get_money(number_of_tokens, e_currency::BTC);
  std::cout << "(user " << m_ID << ") sell " << number_of_tokens << std::endl;
  m_market_ptr->sell(e_currency::BTC, number_of_tokens, m_ID, price);  
}

void c_user::add_money(unsigned int number_of, e_currency currency)
{
  if (currency == e_currency::BTC) {
    m_money_BTC.number_of += number_of;
  }
  if (currency == e_currency::USD) {
    m_money_USD.number_of += number_of;
  }
}

unsigned int c_user::get_money(unsigned int number_of, e_currency currency)
{
  if (currency == e_currency::BTC) {
    if(number_of < m_money_BTC.number_of) {
      m_money_BTC.number_of -= number_of;
      return number_of;
    }
    else {
      unsigned int ret = m_money_BTC.number_of;
      m_money_BTC.number_of = 0;
      return ret;
    }
  }
  if (currency == e_currency::USD) {
    if(number_of < m_money_USD.number_of) {
      m_money_USD.number_of -= number_of;
      return number_of;
    }
    else {
      unsigned int ret = m_money_USD.number_of;
      m_money_USD.number_of = 0;
      return ret;
    }
  }
  return 0;
}

unsigned int c_user::get_ID()
{
  return m_ID;
}
