#include <iostream>
#include <memory>
#include <vector>
#include "c_market.h"
#include "c_user.h"

int main(int argc, char **argv) {
    std::shared_ptr<c_market> market(new c_market);
    std::vector<std::shared_ptr<c_user>> users_vector;
    for(int i = 0; i < 5; ++i) {
      std::shared_ptr<c_user> user_ptr(new c_user(i, market));
      market->add_user(user_ptr);
      users_vector.emplace_back(std::move(user_ptr));
    }
    
    for (unsigned int i = 0; i < users_vector.size(); ++i) {
      users_vector[i]->sell();
      users_vector[(users_vector.size() - 1) - i]->buy();
    }
    // Show users wallets
    for(auto user : users_vector){
      std::cout << "User " << user->get_ID() << "\n BTC: " << user->get_currency_stat(e_currency::BTC) 
      << "\n USD: " << user->get_currency_stat(e_currency::USD) << std::endl;
    }
    
    market->run();
    
    for(auto user : users_vector){
      std::cout << "User " << user->get_ID() << "\n BTC: " << user->get_currency_stat(e_currency::BTC) 
      << "\n USD: " << user->get_currency_stat(e_currency::USD) << std::endl;
    }
    
    
    return 0;
}