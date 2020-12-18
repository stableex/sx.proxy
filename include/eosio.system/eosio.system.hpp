#pragma once

#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract("eosio.system")]] eosio_system : public contract {
public:
    using contract::contract;

    [[eosio::action]]
    void buyrex( const eosio::name from, const eosio::asset amount );

    [[eosio::action]]
    void deposit( const eosio::name owner, const eosio::asset amount );

    [[eosio::action]]
    void voteproducer( const eosio::name voter, const eosio::name proxy, const std::vector<eosio::name> producers );

    using voteproducer_action = eosio::action_wrapper<"voteproducer"_n, &eosio_system::voteproducer>;

    using buyrex_action = eosio::action_wrapper<"buyrex"_n, &eosio_system::buyrex>;
    using deposit_action = eosio::action_wrapper<"deposit"_n, &eosio_system::deposit>;
};