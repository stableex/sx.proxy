#!/bin/bash

# buy REX
cleos push action proxy.sx buyrex '[["flash.sx", "proxy"], "1.0000 EOS"]' -p proxy.sx

# sell REX
cleos push action proxy.sx sellrex '[["flash.sx", "proxy"], "10.0000 EOS"]' -p proxy.sx
cleos push action proxy.sx withdraw '[["flash.sx", "proxy"], "1.0000 EOS"]' -p proxy.sx
