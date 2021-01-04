#include <eosio.token/eosio.token.hpp>
#include <eosio.system/eosio.system.hpp>

#include "proxy.sx.hpp"
#include <cmath>

[[eosio::action]]
void sx::proxy::buyrex( const permission_level account, const asset amount )
{
    if ( !has_auth( get_self() )) require_auth( account.actor );
    eosio_system::deposit_action deposit( "eosio"_n, account );
    eosio_system::buyrex_action buyrex( "eosio"_n, account );

    deposit.send( account.actor, amount );
    buyrex.send( account.actor, amount );
}

[[eosio::action]]
void sx::proxy::sellrex( const permission_level account, const asset amount )
{
    if ( !has_auth( get_self() )) require_auth( account.actor );
    eosio_system::sellrex_action sellrex( "eosio"_n, account );
    sx::proxy::withdraw_action withdraw( get_self(), { get_self(), "active"_n} );

    check( amount.symbol == symbol{"EOS", 4}, "amount must be 4,EOS");

    // calculate REX amount by converted EOS
    const asset rex = { static_cast<int64_t>( ceil(get_rex() * amount.amount) ), {"REX", 4}};

    sellrex.send( account.actor, rex );
    withdraw.send( account );
}

[[eosio::action]]
void sx::proxy::withdraw( const permission_level account )
{
    if ( !has_auth( get_self() )) require_auth( account.actor );

    // get remaining EOS balance from `eosio::rexfund`
    eosio_system::rex_fund_table _rexfund( "eosio"_n, "eosio"_n.value );
    const asset balance = _rexfund.get( account.actor.value, "account does not exists in `rexfund`").balance;

    // withdraw full amount
    eosio_system::withdraw_action withdraw( "eosio"_n, account );
    withdraw.send( account.actor, balance );
}

[[eosio::action]]
void sx::proxy::vote( const permission_level account, const name proxy  )
{
    if ( !has_auth( get_self() )) require_auth( account.actor );
    eosio_system::voteproducer_action voteproducer( "eosio"_n, account );

    std::vector<eosio::name> producers;
    voteproducer.send( account.actor, proxy, producers );
}

double sx::proxy::get_rex()
{
    eosio_system::rex_pool_table rex_pool( "eosio"_n, "eosio"_n.value );
    auto itr = rex_pool.find(0);
    if ( itr == rex_pool.end() ) return 10000; // localhost for TESTING purposes
    return static_cast<double>(itr->total_rex.amount) / itr->total_lendable.amount;
}