# `proxy.sx`

> Manages/rebalance REX staking requirements for contracts

## Quickstart

```bash
# deposit to REX
$ cleos push action dust.sx deposit '[["flash.sx", "proxy"], "1.0000 EOS"]' -p dust.sx

# buy REX
$ cleos push action dust.sx buyrex '[["flash.sx", "proxy"], "1.0000 EOS"]' -p dust.sx
```

## Table of Content

- [TABLE `settings`](#table-settings)
- [ACTION `harvest`](#table-harvest)
- [ACTION `sell`](#table-dust)
- [ACTION `dustall`](#table-dustall)
- [ACTION `setsettings`](#table-setsettings)

## TABLE `settings`

### params

- `{set<name>} accounts` - accounts to dust
- `{vector<extended_symbol>} tokens` - token symbols to dust
- `{time_point_sec} last_harvest` - last harvest timestamp

### example

```json
{
    "accounts": ["flash.sx"],
    "tokens": [
        {"symbol": "8,TAG", "contract": "tagtokenmain"}
    ],
    "last_harvest": "2020-12-14T00:00:00"
}
```

## ACTION `harvest`

Harvest DFS TAG claim

- **authority**: `get_self()` or `account`

### params

- `{name} account` - account name

### Example

```bash
$ cleos push action dust.sx harvest '["flash.sx"]' -p dust.sx
```

## ACTION `sell`

Sell single token for EOS

- **authority**: `get_self()` or `account`

### params

- `{name} account` - account name
- `{extended_symbol} token` - token to dust

### Example

```bash
$ cleos push action dust.sx sell '["flash.sx", ["8,TAG", "tagtokenmain"]]' -p dust.sx
```

## ACTION `dustall`

Dust all tokens from all accounts

- **authority**: `get_self()`

### params

### Example

```bash
$ cleos push action dust.sx dustall '[]' -p dust.sx
```
