#include<eosio/eosio.hpp>
#include<eosio/asset.hpp>

using namespace eosio;

CONTRACT geteos: public contract {
    public:
    using contract::contract;

    ACTION getbalance(name user, asset token) {
        accounts mytoken("eosio.token"_n, user.value);
        symbol sym = token.symbol;
        auto itr = mytoken.require_find(sym.code().raw());

        print(itr->balance);
    }

    private:
        struct [[eosio::table]] account {
            asset    balance; //blaance사용해서잔액확인//

            uint64_t primary_key()const { return balance.symbol.code().raw(); }
         };

         struct [[eosio::table]] currency_stats {
            asset    supply;
            asset    max_supply;
            name     issuer;

            uint64_t primary_key()const { return supply.symbol.code().raw(); }
         };

         typedef multi_index< "accounts"_n, account > accounts;
         typedef multi_index< "stat"_n, currency_stats > stats;
};