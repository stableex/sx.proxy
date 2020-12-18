#!/bin/bash

eosio-cpp proxy.sx.cpp -I include
cleos set contract proxy.sx . proxy.sx.wasm proxy.sx.abi
