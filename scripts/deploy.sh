#!/bin/bash

# unlock wallet
cleos wallet unlock --password $(cat ~/eosio-wallet/.pass)

# create accounts
cleos create account eosio proxy.sx EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio eosio.token EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio flash.sx EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV
cleos create account eosio gateway.sx EOS6MRyAjQq8ud7hVNYcfnVPJqcVpscN5So8BhtHuGYqET5GDW5CV

# deploy
cleos set contract proxy.sx . proxy.sx.wasm proxy.sx.abi
cleos set contract eosio.token include/eosio.token eosio.token.wasm eosio.token.abi

# permission
cleos set account permission proxy.sx active --add-code
cleos set account permission flash.sx proxy proxy.sx --add-code
cleos set action permission flash.sx eosio sellrex proxy
cleos set action permission flash.sx eosio buyrex proxy
cleos set action permission flash.sx eosio withdraw proxy
cleos set action permission flash.sx eosio deposit proxy

# create EOS token
cleos push action eosio.token create '["eosio", "100000000.0000 EOS"]' -p eosio.token
cleos push action eosio.token issue '["eosio", "100000000.0000 EOS", "init"]' -p eosio
cleos transfer eosio flash.sx "500.0000 EOS" "init"
