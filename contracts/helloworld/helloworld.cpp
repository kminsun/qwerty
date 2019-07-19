#include <eosiolib/eosio.hpp>

using namespace eosio;

CONTRACT helloworld: public contract {
    public:
        using contract::contract;

        ACTION hi(name user) {
            
        
            //check(has_auth(get_self()) || (has_auth("jessijessijs"_n)), "wrong");
            //require_auth("qwerty123455"_n && "jessijessijs"_n;

            print("hello, ", user);
        }

        ACTION getaccount(name user) {
            require_auth( get_self() );
            print( is_account(user) );
        }
        
    private:
};