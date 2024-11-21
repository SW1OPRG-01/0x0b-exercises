#include <string>

enum Currency {
  DKK,
  EUR,
  JPY,
  USD,
  NOK,
  SEK,
  ZAR,
};

class Amount {
  public:
    Amount(Currency currency, double amount);
    void add(Currency currency, double amount);
    void convert(Currency currency, double rate);
    std::string to_string();
  private:
    std::string currency_to_string(Currency currency);
    Currency currency;
    double amount;
};