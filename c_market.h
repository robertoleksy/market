#ifndef C_MARKET_H
#define C_MARKET_H

enum class e_currency {
  USD,
  BTC
};

class c_market
{
public:
  void buy(e_currency currency, unsigned int nuber_of);
  void sell(e_currency currency, unsigned int nuber_of);
};

#endif // C_MARKET_H
