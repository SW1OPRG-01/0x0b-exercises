#include <iostream>
#include "amount.h"

Amount::Amount(Currency currency, double amount) : currency(currency), amount(amount) { }

void Amount::add(Currency currency, double amount) {
  if(currency != (*this).currency) {
    std::cerr << "The amount must be specified in currency: " << currency_to_string((*this).currency) << std::endl;
    return;
  }
  (*this).amount += amount;
}

void Amount::convert(Currency currency, double rate) {
  (*this).amount *= rate;
  (*this).currency = currency;
}

std::string Amount::to_string() {
  return currency_to_string(currency) + " " + std::to_string(amount);
}

std::string Amount::currency_to_string(Currency currency) {
  switch (currency)
  {
  case DKK:
    return "DKK";
  case EUR:
    return "EUR";
  case JPY:
    return "JPY";
  case USD:
    return "USD";
  case NOK:
    return "NOK";
  case SEK:
    return "SEK";
  case ZAR:
    return "ZAR";
  }
}