#pragma once

#include <eosio/eosio.hpp>
#include <eosio/asset.hpp>

using namespace eosio;
using namespace std;

class [[eosio::contract("eosio.system")]] eosio_system : public contract {
public:
    using contract::contract;

    // `rex_pool` structure underlying the rex pool table. A rex pool table entry is defined by:
    // - `version` defaulted to zero,
    // - `total_lent` total amount of CORE_SYMBOL in open rex_loans
    // - `total_unlent` total amount of CORE_SYMBOL available to be lent (connector),
    // - `total_rent` fees received in exchange for lent  (connector),
    // - `total_lendable` total amount of CORE_SYMBOL that have been lent (total_unlent + total_lent),
    // - `total_rex` total number of REX shares allocated to contributors to total_lendable,
    // - `namebid_proceeds` the amount of CORE_SYMBOL to be transferred from namebids to REX pool,
    // - `loan_num` increments with each new loan
    struct [[eosio::table,eosio::contract("eosio.system")]] rex_pool {
        uint8_t    version = 0;
        asset      total_lent;
        asset      total_unlent;
        asset      total_rent;
        asset      total_lendable;
        asset      total_rex;
        asset      namebid_proceeds;
        uint64_t   loan_num = 0;

        uint64_t primary_key() const { return 0; }
    };
    typedef eosio::multi_index< "rexpool"_n, rex_pool > rex_pool_table;

    // `rex_balance` structure underlying the rex balance table. A rex balance table entry is defined by:
    // - `version` defaulted to zero,
    // - `owner` the owner of the rex fund,
    // - `vote_stake` the amount of CORE_SYMBOL currently included in owner's vote,
    // - `rex_balance` the amount of REX owned by owner,
    // - `matured_rex` matured REX available for selling
    struct [[eosio::table,eosio::contract("eosio.system")]] rex_balance {
        uint8_t version = 0;
        name    owner;
        asset   vote_stake;
        asset   rex_balance;
        int64_t matured_rex = 0;
        std::deque<std::pair<time_point_sec, int64_t>> rex_maturities; /// REX daily maturity buckets

        uint64_t primary_key()const { return owner.value; }
    };
    typedef eosio::multi_index< "rexbal"_n, rex_balance > rex_balance_table;

    // `rex_fund` structure underlying the rex fund table. A rex fund table entry is defined by:
    // - `version` defaulted to zero,
    // - `owner` the owner of the rex fund,
    // - `balance` the balance of the fund.
    struct [[eosio::table,eosio::contract("eosio.system")]] rex_fund {
        uint8_t version = 0;
        name    owner;
        asset   balance;

        uint64_t primary_key()const { return owner.value; }
    };

    typedef eosio::multi_index< "rexfund"_n, rex_fund > rex_fund_table;


    [[eosio::action]]
    void buyrex( const eosio::name from, const eosio::asset amount );

    [[eosio::action]]
    void sellrex( const eosio::name from, const eosio::asset rex );

    [[eosio::action]]
    void deposit( const eosio::name owner, const eosio::asset amount );

    [[eosio::action]]
    void withdraw( const eosio::name owner, const eosio::asset amount );

    [[eosio::action]]
    void voteproducer( const eosio::name voter, const eosio::name proxy, const std::vector<eosio::name> producers );

    using voteproducer_action = eosio::action_wrapper<"voteproducer"_n, &eosio_system::voteproducer>;

    using buyrex_action = eosio::action_wrapper<"buyrex"_n, &eosio_system::buyrex>;
    using sellrex_action = eosio::action_wrapper<"sellrex"_n, &eosio_system::sellrex>;
    using withdraw_action = eosio::action_wrapper<"withdraw"_n, &eosio_system::withdraw>;
    using deposit_action = eosio::action_wrapper<"deposit"_n, &eosio_system::deposit>;
};