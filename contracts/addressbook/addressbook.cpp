#include<eosio/eosio.hpp>

using namespace eosio;

CONTRACT addressbook: public contract {
    public:
        using contract::contract;

        ACTION findage(uint64_t age) {
            address_index address(get_self(),get_self().value);
            auto forSecondary = address.get_index<"byage"_n>();
            auto itr = forSecondary.require_find(age,"no age");

            print(itr->user, " "  ,itr->age);
        }



        ACTION upsert(name user, std::string first_name, std::string last_name, uint64_t age) {
            require_auth(user);

            address_index forUpsert(get_self(), get_self().value);
            auto itr = forUpsert.find(user.value);

            if(itr == forUpsert.end()) //계정이 존재하지 않음//
            {
            forUpsert.emplace(user, [&](auto&row) {
                row.user = user;
                row.first_name = first_name;
                row.last_name = last_name;
                row.age = age;
                
                });
            }
            else {
            forUpsert.modify(itr, user, [&]( auto& row ) {
                row.user = user;
                row.first_name = first_name;
                row.last_name = last_name;
                row.age = age;
              
                });
            }

        }

        ACTION insert(name user, std::string first_name, std::string last_name, uint64_t age) {
            require_auth(user);

            address_index forInsert(get_self(), get_self().value);
            auto itr = forInsert.find(user.value);

            check(itr == forInsert.end(), "already exists");

            forInsert.emplace(user, [&](auto&row)  { //[&]~는 콜백함수//
                row.user = user;
                row.first_name = first_name;
                row.last_name = last_name;
                row.age = age;
            });
           
            print("insert success");

        }

        ACTION erase(name user) {
            require_auth(user);
            address_index forErase(get_self(), get_self().value); //scope통일//
            auto itr = forErase.require_find(user.value, "no account");
            forErase.erase(itr);
            print("erase success");
        }

    private:
    struct [[eosio::table]] person {      //자료이름(?), 테이블명이 아님//
        name user;
        std::string first_name;
        std::string last_name;
        uint64_t age;

        uint64_t primary_key() const { return user.value; }
        uint64_t by_age() const {return age;}
    };

    typedef multi_index<"peopletwo"_n, person,
    indexed_by<"byage"_n, const_mem_fun<person, uint64_t,&person::by_age>>> address_index; 

};