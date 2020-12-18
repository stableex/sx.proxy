#!/bin/bash

# buy REX
cleos push action proxy.sx buy '[["flash.sx","proxy"], "1.0000 EOS"]' -p proxy.sx

# # set settings
# cleos push action proxy.sx setsettings '[[["flash.sx","proxy"]], [["8,TAG", "tagtokenmain"]]]' -p proxy.sx

# # harvest DFS TAG claim
# cleos push action proxy.sx harvest '["flash.sx"]' -p proxy.sx

# # proxy single token
# cleos push action proxy.sx proxy '["flash.sx", ["8,TAG", "tagtokenmain"]]' -p proxy.sx

# # proxy all tokens from all accounts
# cleos push action proxy.sx proxyall '[]' -p proxy.sx