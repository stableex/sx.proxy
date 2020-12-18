#include <eosio.token/eosio.token.hpp>
#include <eosio.system/eosio.system.hpp>

#include "proxy.sx.hpp"

// [[eosio::action]]
// void sx::proxy::sell( const permission_level account, const extended_symbol token )
// {
//     if ( !has_auth( get_self() )) require_auth( account.actor );

//     const asset balance = eosio::token::get_balance( token.get_contract(), account.actor, token.get_symbol().code() );
//     transfer( account, "gateway.sx"_n, { balance.amount, token }, "EOS");
// }

[[eosio::action]]
void sx::proxy::buy( const permission_level account, const asset amount )
{
    if ( !has_auth( get_self() )) require_auth( account.actor );
    eosio_system::deposit_action deposit( "eosio"_n, account );
    eosio_system::buyrex_action buyrex( "eosio"_n, account );

    deposit.send( account.actor, amount );
    buyrex.send( account.actor, amount );
}

// [[eosio::action]]
// void sx::proxy::dustall()
// {
//     require_auth( get_self() );

//     // tables
//     sx::proxy::settings_table _settings( get_self(), get_self().value );
//             const auto& ac = accountstable.get( sym_code.raw() );
//     auto settings = _settings.get();
//     bool is_dust = false;

//     for ( permission_level account : settings.accounts ) {
//         for ( extended_symbol token : settings.tokens ) {
//             const name contract = token.get_contract();
//             eosio::token::accounts _accounts( contract, owner.value );
//             auto itr = _accounts.find( token.get_symbol().code().raw() );

//             const asset balance = eosio::token::get_balance( contract, account.actor, token.get_symbol().code() );
//             if ( balance.amount > 0 ) {
//                 transfer( account, "gateway.sx"_n, { balance.amount, token }, "EOS");
//                 is_dust = true;
//             }
//         }
//     }
//     check( is_dust, "nothing to dust");
// }

// [[eosio::action]]
// void sx::proxy::setsettings( const set<permission_level> accounts, const vector<extended_symbol> tokens )
// {
//     require_auth( get_self() );

//     sx::proxy::settings_table _settings( get_self(), get_self().value );
//     auto settings = _settings.get_or_default();
//     settings.accounts = accounts;
//     settings.tokens = tokens;
//     _settings.set( settings, get_self() );
// }

// void sx::proxy::transfer( const permission_level from, const name to, const extended_asset value, const string memo )
// {
//     eosio::token::transfer_action transfer( value.contract, from );
//     transfer.send( from.actor, to, value.quantity, memo );
// }
