#ifndef C_MARKET_H
#define C_MARKET_H

enum class e_currency {
  USD,
  BTC
};

class c_market
{
public:
  c_market() = delete;
  c_market(const c_market & mark) = delete;
  c_market & operator = (const c_market &) = delete;
  void buy(e_currency currency, unsigned int nuber_of, unsigned int ID);
  void sell(e_currency currency, unsigned int nuber_of, unsigned int ID);
};

#endif // C_MARKET_H
