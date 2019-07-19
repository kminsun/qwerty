#include<eosio/eosio.hpp>

using namespace eosio;

CONTRACT exampletwo: public contract {
    public:
        using contract::contract;

        ACTION countuser(name user) {
            require_auth(user);
            
            count_index countcount(get_self());
            auto forSecondary = ad.get_index<"bycount"_n>();
            auto itr = forSecondary.require_find();

            if(itr == countcount.end())
            {
                countcount.emplace(user, [&](auto&row) {
                    row.user;
                    row.count=1;
                });
            }
            else {
                countcount.modify(user, [&](auto&row) {
                row.count++;
                });
            }
            print("success");
        }
    

        ACTION findcount(uint64_t count) {
            require_auth(user);
            auto itr = forSecondary.require_find();
        }

        ACTION eraseall() {
            require_auth(get_self());
            count_index forEraseall(get_self(), get_self().value);
            auto itr = forEraseall.begin();
            
            while(itr != forEraseall.end() ) {
                itr = forEraseall.erase(itr);
            }

        }


    private:
        struct [[eosio::table]] count {
            name user;
            uint64_t count;//액션을 실행한 횟수//

            uint64_t primary_key() const { return user.value, get_self().value; }
            uint64_t count() const { return count; }

        };
        typedef multi_index<"counttable"_n, countstruct, 
        indexed_by<"bycount"_n, const_mem_fun<count, uint64_t, &count::by_count>> > count_index;
}